#pragma once

#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>

#include <stdexcept>

QHostAddress parseHostAddress(const QString &hostAddress);

template<typename T>
T getJson(const QJsonDocument &document);

template<>
QJsonDocument getJson<QJsonDocument>(const QJsonDocument &document);

template<>
QJsonObject getJson<QJsonObject>(const QJsonDocument &document);

template<>
QJsonArray getJson<QJsonArray>(const QJsonDocument &document);

template<typename T>
T getJson(const QByteArray &byteArray);

template<typename T>
T getJson(QIODevice &device);

template<typename T>
T getJson(const QString &filename);



template<typename T>
T getJson(const QByteArray &byteArray)
{
    QJsonParseError error;
    auto document = QJsonDocument::fromJson(byteArray, &error);
    if(error.error != QJsonParseError::NoError)
        throw std::runtime_error(QString("Could not parse json: %0").arg(error.errorString()).toStdString());

    return getJson<T>(document);
}

template<typename T>
T getJson(QIODevice &device)
{
    return getJson<T>(device.readAll());
}

template<typename T>
T getJson(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        throw std::runtime_error(QString("Could not open json file %0: %1").arg(filename, file.errorString()).toStdString());

    return getJson<T>(file);
}
