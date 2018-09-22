#include <QCoreApplication>
#include <QDir>
#include <QJsonObject>

#include "utils/jsonutils.h"

#include "webserver.h"

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("webserver");

    const auto configPath = QDir(QCoreApplication::applicationDirPath()).absoluteFilePath(QCoreApplication::applicationName() + QStringLiteral(".json"));
    const auto config = getJson<QJsonObject>(configPath);

    WebServer server(config);
    server.start();

    return app.exec();
}
