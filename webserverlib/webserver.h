#pragma once

#include "webserverlib_global.h"
#include <QObject>

#include <QHash>
#include <QSet>

class QJsonObject;

class WebPlugin;
class WebApplication;
class WebListener;

class WEBSERVERLIB_EXPORT WebServer : public QObject
{
public:
    explicit WebServer(const QJsonObject &config, QObject *parent = Q_NULLPTR);

    void start();

    const QHash<QString, WebPlugin*> &plugins() const;
    const QHash<QString, WebApplication*> &applications() const;
    const QSet<WebListener*> &listeners() const;

private:
    QHash<QString, WebPlugin*> m_plugins;
    QHash<QString, WebApplication*> m_applications;
    QSet<WebListener*> m_listeners;
};
