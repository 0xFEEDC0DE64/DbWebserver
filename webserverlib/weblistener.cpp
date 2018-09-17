#include "weblistener.h"

#include <QJsonObject>
#include <QHash>
#include <QTcpServer>
#include <QDebug>

#include <stdexcept>

#include "utils.h"
#include "httpclientconnection.h"

WebListener::WebListener(const QJsonObject &config, const QHash<QString, WebApplication*> &applications, QObject *parent) :
    QObject(parent)
{
    if(!config.contains(QStringLiteral("hostAddress")))
        throw std::runtime_error("listener does not contain hostAddress");

    const auto hostAddressVal = config.value(QStringLiteral("hostAddress"));
    if(!hostAddressVal.isString())
        throw std::runtime_error("listener hostAddress is not a string");

    m_address = parseHostAddress(hostAddressVal.toString());

    if(!config.contains(QStringLiteral("port")))
        throw std::runtime_error("listener does not contain port");

    const auto portVal = config.value(QStringLiteral("port"));
    if(!portVal.isDouble())
        throw std::runtime_error("listener port is not a number");

    m_port = portVal.toInt();

    m_tcpServer = new QTcpServer(this);

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
                                     .arg(m_address.toString()).arg(m_port).arg(iter.key()).toStdString());

        const auto applicationName = applicationNameVal.toString();

        const auto applicationsIter = applications.find(applicationName);
        if(applicationsIter == applications.constEnd())
            throw std::runtime_error(QString("listener %0:%1 vhost %2 references unknown application %3")
                                     .arg(m_address.toString()).arg(m_port).arg(iter.key(), applicationName).toStdString());

        qDebug() << iter.key() << applicationName;
    }
}

void WebListener::start()
{
    qDebug() << "starting listening" << m_address << m_port;
    if(!m_tcpServer->listen(m_address, m_port))
        throw std::runtime_error(QString("Could not start listening on %0:%1 because %2")
                                 .arg(m_address.toString()).arg(m_port).arg(m_tcpServer->errorString()).toStdString());

    connect(m_tcpServer, &QTcpServer::acceptError, this, &WebListener::acceptError);
    connect(m_tcpServer, &QTcpServer::newConnection, this, &WebListener::newConnection);
}

void WebListener::handleRequest(HttpClientConnection *connection, const HttpRequest &request)
{
    HttpResponse response;
    response.protocol = request.protocol;
    response.statusCode = HttpResponse::StatusCode::OK;
    connection->sendResponse(response, request.path);
}

void WebListener::acceptError(QAbstractSocket::SocketError socketError)
{
    qCritical() << socketError;
}

void WebListener::newConnection()
{
    auto connection = m_tcpServer->nextPendingConnection();
    if(!connection)
        return;

    new HttpClientConnection(*connection, *this);
}
