#include "httpresponse.h"

QString HttpResponse::statusString() const
{
    return statusString(statusCode);
}

QString HttpResponse::statusString(HttpResponse::StatusCode statusCode)
{
    switch(statusCode) {
    case HttpResponse::StatusCode::Continue: return QStringLiteral("Continue");
    case HttpResponse::StatusCode::SwitchingProtocols: return QStringLiteral("Switching Protocols");
    case HttpResponse::StatusCode::Processing: return QStringLiteral("Processing");
    case HttpResponse::StatusCode::EarlyHints: return QStringLiteral("Early Hints");
    case HttpResponse::StatusCode::OK: return QStringLiteral("OK");
    case HttpResponse::StatusCode::Created: return QStringLiteral("Created");
    case HttpResponse::StatusCode::Accepted: return QStringLiteral("Accepted");
    case HttpResponse::StatusCode::NonAuthoritativeInformation: return QStringLiteral("Non-Authoritative Information");
    case HttpResponse::StatusCode::NoContent: return QStringLiteral("No Content");
    case HttpResponse::StatusCode::ResetContent: return QStringLiteral("Reset Content");
    case HttpResponse::StatusCode::PartialContent: return QStringLiteral("Partial Content");
    case HttpResponse::StatusCode::MultiStatus: return QStringLiteral("Multi-Status");
    case HttpResponse::StatusCode::AlreadyReported: return QStringLiteral("Already Reported");
    case HttpResponse::StatusCode::IMUsed: return QStringLiteral("IM Used");
    case HttpResponse::StatusCode::MultipleChoices: return QStringLiteral("Multiple Choices");
    case HttpResponse::StatusCode::MovedPermanently: return QStringLiteral("Moved Permanently");
    case HttpResponse::StatusCode::Found: return QStringLiteral("Found (Moved Temporarily)");
    case HttpResponse::StatusCode::SeeOther: return QStringLiteral("See Other");
    case HttpResponse::StatusCode::NotModified: return QStringLiteral("Not Modified");
    case HttpResponse::StatusCode::UseProxy: return QStringLiteral("Use Proxy");
    case HttpResponse::StatusCode::SwitchProxy: return QStringLiteral("(reserviert)");
    case HttpResponse::StatusCode::TemporaryRedirect: return QStringLiteral("Temporary Redirect");
    case HttpResponse::StatusCode::PermanentRedirect: return QStringLiteral("Permanent Redirect");
    case HttpResponse::StatusCode::BadRequest: return QStringLiteral("Bad Request");
    case HttpResponse::StatusCode::Unauthorized: return QStringLiteral("Unauthorized");
    case HttpResponse::StatusCode::PaymentRequired: return QStringLiteral("Payment Required");
    case HttpResponse::StatusCode::Forbidden: return QStringLiteral("Forbidden");
    case HttpResponse::StatusCode::NotFound: return QStringLiteral("Not Found");
    case HttpResponse::StatusCode::MethodNotAllowed: return QStringLiteral("Method Not Allowed");
    case HttpResponse::StatusCode::NotAcceptable: return QStringLiteral("Not Acceptable");
    case HttpResponse::StatusCode::ProxyAuthenticationRequired: return QStringLiteral("Proxy Authentication Required");
    case HttpResponse::StatusCode::RequestTimeout: return QStringLiteral("Request Timeout");
    case HttpResponse::StatusCode::Conflict: return QStringLiteral("Conflict");
    case HttpResponse::StatusCode::Gone: return QStringLiteral("Gone");
    case HttpResponse::StatusCode::LengthRequired: return QStringLiteral("Length Required");
    case HttpResponse::StatusCode::PreconditionFailed: return QStringLiteral("Precondition Failed");
    case HttpResponse::StatusCode::RequestEntityTooLarge: return QStringLiteral("Request Entity Too Large");
    case HttpResponse::StatusCode::URITooLong: return QStringLiteral("URI Too Long");
    case HttpResponse::StatusCode::UnsupportedMediaType: return QStringLiteral("Unsupported Media Type");
    case HttpResponse::StatusCode::Requestedrangenotsatisfiable: return QStringLiteral("Requested range not satisfiable");
    case HttpResponse::StatusCode::ExpectationFailed: return QStringLiteral("Expectation Failed");
    case HttpResponse::StatusCode::Imateapot: return QStringLiteral("I’m a teapot");
    case HttpResponse::StatusCode::PolicyNotFulfilled: return QStringLiteral("Policy Not Fulfilled");
    case HttpResponse::StatusCode::MisdirectedRequest: return QStringLiteral("Misdirected Request");
    case HttpResponse::StatusCode::UnprocessableEntity: return QStringLiteral("Unprocessable Entity");
    case HttpResponse::StatusCode::Locked: return QStringLiteral("Locked");
    case HttpResponse::StatusCode::FailedDependency: return QStringLiteral("Failed Dependency");
    case HttpResponse::StatusCode::UnorderedCollection: return QStringLiteral("Unordered Collection");
    case HttpResponse::StatusCode::UpgradeRequired: return QStringLiteral("Upgrade Required");
    case HttpResponse::StatusCode::PreconditionRequired: return QStringLiteral("Precondition Required");
    case HttpResponse::StatusCode::TooManyRequests: return QStringLiteral("Too Many Requests");
    case HttpResponse::StatusCode::RequestHeaderFieldsTooLarge: return QStringLiteral("Request Header Fields Too Large");
    case HttpResponse::StatusCode::NoResponse: return QStringLiteral("No Response");
    case HttpResponse::StatusCode::Therequestshouldberetriedafterdoingtheappropriateaction: return QStringLiteral("The request should be retried after doing the appropriate action");
    case HttpResponse::StatusCode::UnavailableForLegalReasons: return QStringLiteral("Unavailable For Legal Reasons");
    case HttpResponse::StatusCode::ClientClosedRequest: return QStringLiteral("Client Closed Request");
    case HttpResponse::StatusCode::InternalServerError: return QStringLiteral("Internal Server Error");
    case HttpResponse::StatusCode::NotImplemented: return QStringLiteral("Not Implemented");
    case HttpResponse::StatusCode::BadGateway: return QStringLiteral("Bad Gateway");
    case HttpResponse::StatusCode::ServiceUnavailable: return QStringLiteral("Service Unavailable");
    case HttpResponse::StatusCode::GatewayTimeout: return QStringLiteral("Gateway Timeout");
    case HttpResponse::StatusCode::HTTPVersionnotsupported: return QStringLiteral("HTTP Version not supported");
    case HttpResponse::StatusCode::VariantAlsoNegotiates: return QStringLiteral("Variant Also Negotiates");
    case HttpResponse::StatusCode::InsufficientStorage: return QStringLiteral("Insufficient Storage");
    case HttpResponse::StatusCode::LoopDetected: return QStringLiteral("Loop Detected");
    case HttpResponse::StatusCode::BandwidthLimitExceeded: return QStringLiteral("Bandwidth Limit Exceeded");
    case HttpResponse::StatusCode::NotExtended: return QStringLiteral("Not Extended");
    case HttpResponse::StatusCode::NetworkAuthenticationRequired: return QStringLiteral("Network Authentication Required");
    }
}

const QString HttpResponse::HEADER_ACCEPTRANGES(QStringLiteral("Accept-Ranges"));
const QString HttpResponse::HEADER_AGE(QStringLiteral("Age"));
const QString HttpResponse::HEADER_ALLOW(QStringLiteral("Allow"));
const QString HttpResponse::HEADER_CACHECONTROL(QStringLiteral("Cache-Control"));
const QString HttpResponse::HEADER_CONNECTION(QStringLiteral("Connection"));
const QString HttpResponse::HEADER_CONTENTENCODING(QStringLiteral("Content-Encoding"));
const QString HttpResponse::HEADER_CONTENTLANGUAGE(QStringLiteral("Content-Language"));
const QString HttpResponse::HEADER_CONTENTLENGTH(QStringLiteral("Content-Length"));
const QString HttpResponse::HEADER_CONTENTLOCATION(QStringLiteral("Content-Location"));
const QString HttpResponse::HEADER_CONTENTMD5(QStringLiteral("Content-MD5"));
const QString HttpResponse::HEADER_CONTENTDISPOSITION(QStringLiteral("Content-Disposition"));
const QString HttpResponse::HEADER_CONTENTRANGE(QStringLiteral("Content-Range"));
const QString HttpResponse::HEADER_CONTENTSECURITYPOLICY(QStringLiteral("Content-Security-Policy"));
const QString HttpResponse::HEADER_CONTENTTYPE(QStringLiteral("Content-Type"));
const QString HttpResponse::HEADER_DATE(QStringLiteral("Date"));
const QString HttpResponse::HEADER_ETAG(QStringLiteral("ETag"));
const QString HttpResponse::HEADER_EXPIRES(QStringLiteral("Expires"));
const QString HttpResponse::HEADER_LASTMODIFIED(QStringLiteral("Last-Modified"));
const QString HttpResponse::HEADER_LINK(QStringLiteral("Link"));
const QString HttpResponse::HEADER_LOCATION(QStringLiteral("Location"));
const QString HttpResponse::HEADER_P3P(QStringLiteral("P3P"));
const QString HttpResponse::HEADER_PRAGMA(QStringLiteral("Pragma"));
const QString HttpResponse::HEADER_PROXYAUTHENTICATE(QStringLiteral("Proxy-Authenticate"));
const QString HttpResponse::HEADER_REFRESH(QStringLiteral("Refresh"));
const QString HttpResponse::HEADER_RETRYAFTER(QStringLiteral("Retry-After"));
const QString HttpResponse::HEADER_SERVER(QStringLiteral("Server"));
const QString HttpResponse::HEADER_SETCOOKIE(QStringLiteral("Set-Cookie"));
const QString HttpResponse::HEADER_TRAILER(QStringLiteral("Trailer"));
const QString HttpResponse::HEADER_TRANSFERENCODING(QStringLiteral("Transfer-Encoding"));
const QString HttpResponse::HEADER_VARY(QStringLiteral("Vary"));
const QString HttpResponse::HEADER_VIA(QStringLiteral("Via"));
const QString HttpResponse::HEADER_WARNING(QStringLiteral("Warning"));
const QString HttpResponse::HEADER_WWWAUTHENTICATE(QStringLiteral("WWW-Authenticate"));
