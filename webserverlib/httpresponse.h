#pragma once

#include "webserverlib_global.h"

#include <QString>
#include <QHash>

struct WEBSERVERLIB_EXPORT HttpResponse {
    enum class StatusCode {
        // 1xx Informational responses
        Continue = 100,                                                 // Continue
        SwitchingProtocols = 101,                                       // Switching Protocols
        Processing = 102,                                               // Processing
        EarlyHints = 103,                                               // Early Hints

        // 2xx Success
        OK = 200,                                                       // OK
        Created = 201,                                                  // Created
        Accepted = 202,                                                 // Accepted
        NonAuthoritativeInformation = 203,                              // Non-Authoritative Information
        NoContent = 204,                                                // No Content
        ResetContent = 205,                                             // Reset Content
        PartialContent = 206,                                           // Partial Content
        MultiStatus = 207,                                              // Multi-Status
        AlreadyReported = 208,                                          // Already Reported
        IMUsed = 226,                                                   // IM Used

        // 3xx Redirection
        MultipleChoices = 300,                                          // Multiple Choices
        MovedPermanently = 301,                                         // Moved Permanently
        Found = 302,                                                    // Found (Moved Temporarily)
        SeeOther = 303,                                                 // See Other
        NotModified = 304,                                              // Not Modified
        UseProxy = 305,                                                 // Use Proxy
        SwitchProxy = 306,                                              // (reserviert)
        TemporaryRedirect = 307,                                        // Temporary Redirect
        PermanentRedirect = 308,                                        // Permanent Redirect

        // 4xx Client errors
        BadRequest = 400,                                               // Bad Request
        Unauthorized = 401,                                             // Unauthorized
        PaymentRequired = 402,                                          // Payment Required
        Forbidden = 403,                                                // Forbidden
        NotFound = 404,                                                 // Not Found
        MethodNotAllowed = 405,                                         // Method Not Allowed
        NotAcceptable = 406,                                            // Not Acceptable
        ProxyAuthenticationRequired = 407,                              // Proxy Authentication Required
        RequestTimeout = 408,                                           // Request Timeout
        Conflict = 409,                                                 // Conflict
        Gone = 410,                                                     // Gone
        LengthRequired = 411,                                           // Length Required
        PreconditionFailed = 412,                                       // Precondition Failed
        RequestEntityTooLarge = 413,                                    // Request Entity Too Large
        URITooLong = 414,                                               // URI Too Long
        UnsupportedMediaType = 415,                                     // Unsupported Media Type
        Requestedrangenotsatisfiable = 416,                             // Requested range not satisfiable
        ExpectationFailed = 417,                                        // Expectation Failed
        Imateapot = 418,                                                // I’m a teapot
        PolicyNotFulfilled = 420,                                       // Policy Not Fulfilled
        MisdirectedRequest = 421,                                       // Misdirected Request
        UnprocessableEntity = 422,                                      // Unprocessable Entity
        Locked = 423,                                                   // Locked
        FailedDependency = 424,                                         // Failed Dependency
        UnorderedCollection = 425,                                      // Unordered Collection
        UpgradeRequired = 426,                                          // Upgrade Required
        PreconditionRequired = 428,                                     // Precondition Required
        TooManyRequests = 429,                                          // Too Many Requests
        RequestHeaderFieldsTooLarge = 431,                              // Request Header Fields Too Large
        NoResponse = 444,                                               // No Response
        Therequestshouldberetriedafterdoingtheappropriateaction = 449,  // The request should be retried after doing the appropriate action
        UnavailableForLegalReasons = 451,                               // Unavailable For Legal Reasons
        ClientClosedRequest = 499,                                      // Client Closed Request

        // 5xx Server errors
        InternalServerError = 500,                                      // Internal Server Error
        NotImplemented = 501,                                           // Not Implemented
        BadGateway = 502,                                               // Bad Gateway
        ServiceUnavailable = 503,                                       // Service Unavailable
        GatewayTimeout = 504,                                           // Gateway Timeout
        HTTPVersionnotsupported = 505,                                  // HTTP Version not supported
        VariantAlsoNegotiates = 506,                                    // Variant Also Negotiates
        InsufficientStorage = 507,                                      // Insufficient Storage
        LoopDetected = 508,                                             // Loop Detected
        BandwidthLimitExceeded = 509,                                   // Bandwidth Limit Exceeded
        NotExtended = 510,                                              // Not Extended
        NetworkAuthenticationRequired = 511,                            // Network Authentication Required
    };

    QString protocol;
    StatusCode statusCode;
    QHash<QString, QString> headers;

    QString statusString() const;
    static QString statusString(StatusCode statusCode);

    static const QString HEADER_ACCEPTRANGES;
    static const QString HEADER_AGE;
    static const QString HEADER_ALLOW;
    static const QString HEADER_CACHECONTROL;
    static const QString HEADER_CONNECTION;
    static const QString HEADER_CONTENTENCODING;
    static const QString HEADER_CONTENTLANGUAGE;
    static const QString HEADER_CONTENTLENGTH;
    static const QString HEADER_CONTENTLOCATION;
    static const QString HEADER_CONTENTMD5;
    static const QString HEADER_CONTENTDISPOSITION;
    static const QString HEADER_CONTENTRANGE;
    static const QString HEADER_CONTENTSECURITYPOLICY;
    static const QString HEADER_CONTENTTYPE;
    static const QString HEADER_DATE;
    static const QString HEADER_ETAG;
    static const QString HEADER_EXPIRES;
    static const QString HEADER_LASTMODIFIED;
    static const QString HEADER_LINK;
    static const QString HEADER_LOCATION;
    static const QString HEADER_P3P;
    static const QString HEADER_PRAGMA;
    static const QString HEADER_PROXYAUTHENTICATE;
    static const QString HEADER_REFRESH;
    static const QString HEADER_RETRYAFTER;
    static const QString HEADER_SERVER;
    static const QString HEADER_SETCOOKIE;
    static const QString HEADER_TRAILER;
    static const QString HEADER_TRANSFERENCODING;
    static const QString HEADER_VARY;
    static const QString HEADER_VIA;
    static const QString HEADER_WARNING;
    static const QString HEADER_WWWAUTHENTICATE;
};
