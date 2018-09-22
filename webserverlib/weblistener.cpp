#include "weblistener.h"

#include <QJsonObject>
#include <QHash>
#include <QTcpServer>
#include <QDebug>

#include <stdexcept>

#include "utils/netutils.h"

#include "webserver.h"
#include "httpclientconnection.h"
#include "webapplication.h"

WebListener::WebListener(const QJsonObject &config, WebServer &webServer) :
    QObject(&webServer), m_webServer(webServer)
{
    if(!config.contains(QStringLiteral("hostAddress")))
        throw std::runtime_error("listener does not contain hostAddress");

    const auto hostAddressVal = config.value(QStringLiteral("hostAddress"));
    if(!hostAddressVal.isString())
        throw std::runtime_error("listener hostAddress is not a string");

    m_hostAddress = parseHostAddress(hostAddressVal.toString());

    if(!config.contains(QStringLiteral("port")))
        throw std::runtime_error("listener does not contain port");

    const auto portVal = config.value(QStringLiteral("port"));
    if(!portVal.isDouble())
        throw std::runtime_error("listener port is not a number");

    m_port = portVal.toInt();

    m_server = new QTcpServer(this);

    if(!config.contains(QStringLiteral("vhosts")))
        throw std::runtime_error("listener does not contain vhosts");

    const auto vhostsVal = config.value(QStringLiteral("vhosts"));
    if(!vhostsVal.isObject())
        throw std::runtime_error("listener vhosts is not an object");

    const auto vhosts = vhostsVal.toObject();
    for(auto iter = vhosts.constBegin(); iter != vhosts.constEnd(); iter++)
    {
        const auto applicationNameVal = iter.value();
        if(!applicationNameVal.isString())
            throw std::runtime_error(QString("listener %0:%1 vhost %2 is not a string")
                                     .arg(m_hostAddress.toString()).arg(m_port).arg(iter.key()).toStdString());

        const auto applicationName = applicationNameVal.toString();

        const auto applicationsIter = m_webServer.applications().find(applicationName);
        if(applicationsIter == m_webServer.applications().constEnd())
            throw std::runtime_error(QString("listener %0:%1 vhost %2 references unknown application %3")
                                     .arg(m_hostAddress.toString()).arg(m_port).arg(iter.key(), applicationName).toStdString());

        m_hosts.insert(iter.key(), *applicationsIter);
    }
}

void WebListener::start()
{
    if(!m_server->listen(m_hostAddress, m_port))
        throw std::runtime_error(QString("Could not start listening on %0:%1 because %2")
                                 .arg(m_hostAddress.toString()).arg(m_port).arg(m_server->errorString()).toStdString());

    connect(m_server, &QTcpServer::acceptError, this, &WebListener::acceptError);
    connect(m_server, &QTcpServer::newConnection, this, &WebListener::newConnection);
}

void WebListener::handleRequest(HttpClientConnection *connection, const HttpRequest &request)
{
    QString host;

    {
        const auto hostHeaderIter = qAsConst(request.headers).find(HttpRequest::HEADER_HOST);
        if(hostHeaderIter != request.headers.constEnd())
            host = hostHeaderIter.value();
    }

    if(host.isEmpty())
    {
        const auto iter = m_hosts.find(QStringLiteral("*"));
        if(iter == m_hosts.constEnd())
        {
            HttpResponse response;
            response.protocol = request.protocol;
            response.statusCode = HttpResponse::StatusCode::BadRequest;
            connection->sendResponse(response, tr("Your request didn't contain a Host header and there is no fallback host configured!"));
            return;
        }

        iter.value()->handleRequest(connection, request);
        return;
    }

    auto iter = m_hosts.find(host);
    if(iter == m_hosts.constEnd())
    {
        iter = m_hosts.find(QStringLiteral("*"));
        if(iter == m_hosts.constEnd())
        {
            HttpResponse response;
            response.protocol = request.protocol;
            response.statusCode = HttpResponse::StatusCode::BadRequest;
            connection->sendResponse(response, tr("Your requested Host \"%0\" is unknown and there is no fallback host configured!"));
            return;
        }
    }

    iter.value()->handleRequest(connection, request);
}

void WebListener::acceptError(QAbstractSocket::SocketError socketError)
{
    qCritical() << socketError;
}

void WebListener::newConnection()
{
    auto socket = m_server->nextPendingConnection();
    if(!socket)
    {
        qWarning() << "null socket received";
        return;
    }

    auto client = new HttpClientConnection(*socket, *this);
    m_clients.insert(client);
    connect(client, &QObject::destroyed, this, [this, client](){
        m_clients.remove(client);
    });
}
