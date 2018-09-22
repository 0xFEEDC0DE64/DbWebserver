#include "webserver.h"

#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include <QLibrary>
#include <QPluginLoader>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include <stdexcept>

#include "webplugin.h"
#include "webapplication.h"
#include "weblistener.h"

WebServer::WebServer(const QJsonObject &config, QObject *parent) :
    QObject(parent)
{
    {
        QDir dir(QDir(QCoreApplication::applicationDirPath()).absoluteFilePath(QStringLiteral("plugins/") + QCoreApplication::applicationName()));
        for(const auto &fileInfo : dir.entryInfoList(QDir::Files | QDir::NoSymLinks))
        {
            if(!QLibrary::isLibrary(fileInfo.filePath()))
            {
                qWarning() << "skipping" << fileInfo.fileName() << "because no QLibrary";
                continue; // to skip windows junk files
            }

            QPluginLoader pluginLoader(fileInfo.filePath());
            if(!pluginLoader.load())
            {
                qCritical() << "error loading plugin" << fileInfo.fileName() << "because" << pluginLoader.errorString();
                continue;
            }

            if(auto plugin = qobject_cast<WebPlugin*>(pluginLoader.instance()))
            {
                const auto pluginName = plugin->pluginName();
                if(m_plugins.contains(pluginName))
                    throw std::runtime_error(QString("duplicate plugin %0").arg(pluginName).toStdString());
                m_plugins.insert(pluginName, plugin);
            }
            else
                qCritical() << "plugin" << fileInfo.fileName() << "could not be casted to WebPlugin";
        }
    }

    if(!config.contains(QStringLiteral("applications")))
        throw std::runtime_error("settings does not contain a applications");

    {
        const auto applicationsVal = config.value(QStringLiteral("applications"));
        if(!applicationsVal.isObject())
            throw std::runtime_error("applications is not a json object");

        const auto applicationsList = applicationsVal.toObject();
        for(auto iter = applicationsList.constBegin(); iter != applicationsList.constEnd(); iter++)
        {
            const auto applicationVal = iter.value();
            if(!applicationVal.isObject())
                throw std::runtime_error(QString("application %0 is not a json object").arg(iter.key()).toStdString());

            auto application = applicationVal.toObject();
            if(!application.contains(QStringLiteral("_pluginName")))
                throw std::runtime_error(QString("application %0 does not contain a _pluginName").arg(iter.key()).toStdString());

            const auto pluginNameVal = application.take(QStringLiteral("_pluginName"));
            if(!pluginNameVal.isString())
                throw std::runtime_error(QString("application %0 pluginName is not a string").arg(iter.key()).toStdString());

            auto pluginName = pluginNameVal.toString();

            const auto pluginsIter = m_plugins.find(pluginName);
            if(pluginsIter == m_plugins.constEnd())
                throw std::runtime_error(QString("application %0 references not installed plugin %1").arg(iter.key(), pluginName).toStdString());

            m_applications.insert(iter.key(), pluginsIter.value()->createApplication(application, *this));
        }
    }

    if(!config.contains(QStringLiteral("listeners")))
        throw std::runtime_error("settings does not contain a listeners");

    {
        const auto listenersVal = config.value(QStringLiteral("listeners"));
        if(!listenersVal.isArray())
            throw std::runtime_error("listeners is not a json array");

        const auto listenersList = listenersVal.toArray();
        for(auto iter = listenersList.constBegin(); iter != listenersList.constEnd(); iter++)
        {
            const auto listenerVal = *iter;
            if(!listenerVal.isObject())
                throw std::runtime_error(QString("listener %0 is not an object").arg(std::distance(listenersList.constBegin(), iter)).toStdString());

            const auto listener = listenerVal.toObject();

            m_listeners.insert(new WebListener(listener, *this));
        }
    }
}

void WebServer::start()
{
    for(auto iter = m_applications.constBegin(); iter != m_applications.constEnd(); iter++)
        iter.value()->start();

    for(auto listener : m_listeners)
        listener->start();
}

const QHash<QString, WebPlugin *> &WebServer::plugins() const
{
    return m_plugins;
}

const QHash<QString, WebApplication *> &WebServer::applications() const
{
    return m_applications;
}

const QSet<WebListener *> &WebServer::listeners() const
{
    return m_listeners;
}
