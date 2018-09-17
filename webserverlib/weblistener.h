#pragma once

#include <QObject>
#include "webserverlib_global.h"

#include <QAbstractSocket>
#include <QHostAddress>

class QJsonObject;
template <class Key, class T> class QHash;
class QTcpServer;

class WebApplication;
class HttpClientConnection;
class HttpRequest;

class WEBSERVERLIB_EXPORT WebListener : public QObject
{
    Q_OBJECT

public:
    WebListener(const QJsonObject &config, const QHash<QString, WebApplication*> &applications, QObject *parent = Q_NULLPTR);

    void start();
    void handleRequest(HttpClientConnection *connection, const HttpRequest &request);

private Q_SLOTS:
    void acceptError(QAbstractSocket::SocketError socketError);
    void newConnection();

private:
    QTcpServer *m_tcpServer;
    QHostAddress m_address;
    quint16 m_port;
};
