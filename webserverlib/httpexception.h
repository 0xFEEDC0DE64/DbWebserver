#pragma once

#include <stdexcept>

#include <QString>

#include <string>

#include "httprequest.h"

class HttpException : public std::runtime_error
{
public:
    explicit HttpException(const HttpRequest &httpRequest, const QString &what_arg);
    explicit HttpException(const HttpRequest &httpRequest, const std::string &what_arg);
    explicit HttpException(const HttpRequest &httpRequest, const char *what_arg);

    const HttpRequest &httpRequest() const;

private:
    HttpRequest m_httpRequest;
};
