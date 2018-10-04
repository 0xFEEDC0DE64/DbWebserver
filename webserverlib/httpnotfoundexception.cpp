#include "httpnotfoundexception.h"

HttpNotFoundException::HttpNotFoundException(const HttpRequest &httpRequest) :
    HttpException(httpRequest, QString("File not found: %0").arg(httpRequest.path))
{
}
