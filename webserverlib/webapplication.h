#pragma once

#include <QObject>
#include "webserverlib_global.h"

class WEBSERVERLIB_EXPORT WebApplication : public QObject
{
    Q_OBJECT

public:
    WebApplication(QObject *parent = Q_NULLPTR);

    virtual void start() = 0;
};
