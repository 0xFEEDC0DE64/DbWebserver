#pragma once

#include <QObject>
#include <QIODevice>

#include <memory>

#include "httpcontainers.h"

class QTcpSocket;

class WebListener;

class HttpClientConnection : public QObject
{
    Q_OBJECT

public:
    explicit HttpClientConnection(QTcpSocket &socket, WebListener &WebListener);

    void sendResponse(const HttpResponse &response);
    void sendResponse(HttpResponse response, const QByteArray &byteArray);
    void sendResponse(HttpResponse response, const QString &string);
    void sendResponse(HttpResponse response, std::unique_ptr<QIODevice> &&device);

private Q_SLOTS:
    void readyRead();
    void bytesWritten();

private:
    void clearRequest();

    QTcpSocket &m_socket;
    WebListener &m_webListener;

    QByteArray m_buffer;
    enum { RequestLine, Headers, RequestBody, WaitingForResponse, SendingResponse } m_state;
    int m_bodyLength;

    HttpRequest m_request;

    std::unique_ptr<QIODevice> m_sendingDeivce;
};
