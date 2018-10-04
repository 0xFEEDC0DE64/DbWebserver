#pragma once

#include "httpexception.h"

#include "httprequest.h"

class HttpNotFoundException : public HttpException
{
public:
    explicit HttpNotFoundException(const HttpRequest &httpRequest);
};
