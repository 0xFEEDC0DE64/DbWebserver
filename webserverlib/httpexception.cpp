#include "httpexception.h"

HttpException::HttpException(const HttpRequest &httpRequest, const QString &what_arg) :
    std::runtime_error(what_arg.toStdString()), m_httpRequest(httpRequest)
{
}

HttpException::HttpException(const HttpRequest &httpRequest, const std::string &what_arg) :
    std::runtime_error(what_arg), m_httpRequest(httpRequest)
{
}

HttpException::HttpException(const HttpRequest &httpRequest, const char *what_arg) :
    std::runtime_error(what_arg), m_httpRequest(httpRequest)
{
}

const HttpRequest &HttpException::httpRequest() const
{
    return m_httpRequest;
}
