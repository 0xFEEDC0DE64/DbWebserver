#include "httpclientconnection.h"

#include <QTcpSocket>
#include <QTextStream>
#include <QFileDevice>
#include <QFileInfo>
#include <QMimeDatabase>
#include <QRegularExpression>
#include <QUrl>

#include "weblistener.h"

const int HttpClientConnection::m_bufferSize(1024*1024*4);

HttpClientConnection::HttpClientConnection(QTcpSocket &socket, WebListener &webServer) :
    QObject(&webServer),
    m_socket(socket),
    m_webListener(webServer),
    m_state(RequestLine),
    m_bodyLength(-1)
{
    m_socket.setParent(this);

    connect(&m_socket, &QIODevice::readyRead, this, &HttpClientConnection::readyRead);
    connect(&m_socket, &QTcpSocket::disconnected, this, &QObject::deleteLater);
}

void HttpClientConnection::sendResponse(const HttpResponse &response)
{
    if(m_state != WaitingForResponse)
    {
        qCritical() << "sending a response now is not allowed!";
        return;
    }

    QTextStream stream(&m_socket);
    stream << response.protocol << ' ' << int(response.statusCode) << ' ' << response.statusString() << endl;

    for(auto iter = response.headers.constBegin(); iter != response.headers.constEnd(); iter++)
        stream << iter.key() << ": " << iter.value() << endl;

    stream << endl;
}

void HttpClientConnection::sendResponse(HttpResponse response, const QByteArray &byteArray)
{
    if(m_state != WaitingForResponse)
    {
        qCritical() << "sending a response now is not allowed!";
        return;
    }

    response.headers.insert(HttpResponse::HEADER_CONTENTLENGTH, QString::number(byteArray.length()));
    sendResponse(response);
    m_socket.write(byteArray);
    m_state = RequestLine;
}

void HttpClientConnection::sendResponse(HttpResponse response, const QString &string)
{
    if(m_state != WaitingForResponse)
    {
        qCritical() << "sending a response now is not allowed!";
        return;
    }

    sendResponse(response, string.toUtf8());
    m_state = RequestLine;
}

void HttpClientConnection::sendResponse(HttpResponse response, std::unique_ptr<QIODevice> &&device)
{
    if(m_state != WaitingForResponse)
        throw std::runtime_error("sending a response now is not allowed!");

    if(!device->isReadable())
        throw std::runtime_error("device is not readable");

    if(device->isSequential())
        throw std::runtime_error("sequental device not supported yet");

    response.headers.insert(HttpResponse::HEADER_CONTENTLENGTH, QString::number(device->size()));

    m_sendingDeivce = std::move(device);

    sendResponse(response);

    connect(&m_socket, &QIODevice::bytesWritten, this, &HttpClientConnection::bytesWritten);
    bytesWritten();

    m_state = SendingResponse;
}

void HttpClientConnection::sendResponse(HttpResponse response, std::unique_ptr<QFileDevice> &&device)
{
    if(m_state != WaitingForResponse)
        throw std::runtime_error("sending a response now is not allowed!");

    if(!device->isReadable())
        throw std::runtime_error("device is not readable");

    if(device->isSequential())
        throw std::runtime_error("sequental device not supported yet");

    const QFileInfo fileInfo(device->fileName());

    response.headers.insert(HttpResponse::HEADER_CONTENTLENGTH, QString::number(fileInfo.size() - device->pos()));

    {
        static const QMimeDatabase mimeDatabse;
        const auto mimeType = mimeDatabse.mimeTypeForFile(fileInfo);
        if(mimeType.isValid())
            response.headers.insert(HttpResponse::HEADER_CONTENTTYPE, mimeType.name());
    }

    m_sendingDeivce = std::move(device);

    sendResponse(response);

    connect(&m_socket, &QIODevice::bytesWritten, this, &HttpClientConnection::bytesWritten);
    bytesWritten();

    m_state = SendingResponse;
}

void HttpClientConnection::readyRead()
{
    m_buffer.append(m_socket.readAll());

    switch(m_state)
    {
    case RequestLine:
    case Headers:
    {
        int index;
        while((index = m_buffer.indexOf(QByteArrayLiteral("\r\n"))) != -1)
        {
            QString line(m_buffer.left(index));
            m_buffer.remove(0, index + 2);

            switch(m_state)
            {
            case RequestLine:
            {
                auto parts = line.split(QLatin1Char(' '));
                if(parts.count() != 3)
                {
                    m_socket.close();
                    return;
                }

                m_request.method = parts.at(0).toUtf8();
                m_request.path = QUrl::fromPercentEncoding(parts.at(1).toUtf8());
                m_request.protocol = parts.at(2).toUtf8();

                m_state = Headers;
                continue;
            }
            case Headers:
            {
                if(!line.isEmpty())
                {
                    static const QRegularExpression regex(QStringLiteral("^ *([^ :]+) *: *(.*) *$"));

                    auto match = regex.match(line);
                    if(!match.hasMatch())
                        qWarning() << "ignoring invalid" << line;

                    if(m_request.headers.contains(match.captured(1)))
                        qWarning() << "duplicate header" << match.captured(1);

                    m_request.headers.insert(match.captured(1), match.captured(2));
                }
                else
                {
                    if(m_request.headers.contains(QStringLiteral("Content-Length")))
                    {
                        m_bodyLength = m_request.headers.value(QStringLiteral("Content-Length")).toInt();
                        m_state = RequestBody;
                        goto hatschi;
                    }
                    else
                    {
                        m_state = WaitingForResponse;
                        m_webListener.handleRequest(this, m_request);
                        clearRequest();
                    }
                }
                break;
            }
            default: qt_noop();
            }
        }
        return;
    }
    case RequestBody:
    hatschi:
    {
        auto length = qMin(m_bodyLength - m_request.body.count(), m_buffer.count());
        m_request.body.append(m_buffer.left(length));
        m_buffer.remove(0, length);

        if(m_request.body.count() == m_bodyLength)
        {
            if(!m_buffer.isEmpty())
                qCritical() << "received more than expected!";

            m_state = WaitingForResponse;
            m_webListener.handleRequest(this, m_request);
            clearRequest();
        }

        break;
    }
    default: qt_noop();
    }
}

void HttpClientConnection::bytesWritten()
{
    if(m_socket.bytesToWrite() >= m_bufferSize)
        return;

    if(m_socket.bytesToWrite() == 0 && m_sendingDeivce->bytesAvailable() == 0)
    {
        m_state = RequestLine;
        disconnect(&m_socket, &QIODevice::bytesWritten, this, &HttpClientConnection::bytesWritten);
        m_sendingDeivce.reset();
        return;
    }

    auto buffer = m_sendingDeivce->read(m_bufferSize);
    m_socket.write(buffer);
}

void HttpClientConnection::clearRequest()
{
    m_request.headers.clear();
    m_request.body.clear();
}
