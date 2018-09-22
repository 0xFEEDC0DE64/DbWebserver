#pragma once

#include "webserverlib_global.h"

#include <QString>
#include <QHash>
#include <QByteArray>

struct WEBSERVERLIB_EXPORT HttpRequest {
    QString method;
    QString path;
    QString protocol;
    QHash<QString, QString> headers;
    QByteArray body;

    static const QString HEADER_ACCEPT;
    static const QString HEADER_ACCEPTCHARSET;
    static const QString HEADER_ACCEPTENCODING;
    static const QString HEADER_ACCEPTLANGUAGE;
    static const QString HEADER_AUTHORIZATION;
    static const QString HEADER_CACHECONTROL;
    static const QString HEADER_CONNECTION;
    static const QString HEADER_COOKIE;
    static const QString HEADER_CONTENTLENGTH;
    static const QString HEADER_CONTENTMD5;
    static const QString HEADER_CONTENTTYPE;
    static const QString HEADER_DATE;
    static const QString HEADER_EXPECT;
    static const QString HEADER_FORWARDED;
    static const QString HEADER_FROM;
    static const QString HEADER_HOST;
    static const QString HEADER_IFMATCH;
    static const QString HEADER_IFMODIFIEDSINCE;
    static const QString HEADER_IFNONEMATCH;
    static const QString HEADER_IFRANGE;
    static const QString HEADER_IFUNMODIFIEDSINCE;
    static const QString HEADER_MAXFORWARDS;
    static const QString HEADER_PRAGMA;
    static const QString HEADER_PROXYAUTHORIZATION;
    static const QString HEADER_RANGE;
    static const QString HEADER_REFERER;
    static const QString HEADER_TE;
    static const QString HEADER_TRANSFERENCODING;
    static const QString HEADER_UPGRADE;
    static const QString HEADER_USERAGENT;
    static const QString HEADER_VIA;
    static const QString HEADER_WARNING;
};
