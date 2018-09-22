#pragma once

#include <QObject>
#include "webserverlib_global.h"

class QJsonObject;

class WebApplication;
class WebServer;

class WEBSERVERLIB_EXPORT WebPlugin : public QObject
{
    Q_OBJECT

public:
    WebPlugin(QObject *parent = Q_NULLPTR);

    virtual QString pluginName() const = 0;
    virtual WebApplication *createApplication(const QJsonObject &config, WebServer &webServer) const = 0;
};

Q_DECLARE_INTERFACE(WebPlugin, "dbsoftware.webserver.plugin/1.0")
