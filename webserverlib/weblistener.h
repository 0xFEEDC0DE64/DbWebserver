#pragma once

#include <QObject>
#include "webserverlib_global.h"

#include <QAbstractSocket>
#include <QHostAddress>
#include <QHash>
#include <QSet>

class QJsonObject;
class QTcpServer;

class WebServer;
class WebApplication;
class HttpClientConnection;
class HttpRequest;

class WEBSERVERLIB_EXPORT WebListener : public QObject
{
    Q_OBJECT

public:
    WebListener(const QJsonObject &config, WebServer &webServer);

    void start();
    void handleRequest(HttpClientConnection *connection, const HttpRequest &request);

private Q_SLOTS:
    void acceptError(QAbstractSocket::SocketError socketError);
    void newConnection();

private:
    WebServer &m_webServer;

    QHostAddress m_hostAddress;
    quint16 m_port;
    QTcpServer *m_server;
    QHash<QString, WebApplication*> m_hosts;
    QSet<HttpClientConnection*> m_clients;
};
