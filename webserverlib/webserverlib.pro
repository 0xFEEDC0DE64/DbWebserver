QT += core network
QT -= gui widgets

PROJECT_ROOT = ../..

DEFINES += WEBSERVERLIB_LIBRARY

SOURCES += \
    weblistener.cpp \
    webapplication.cpp \
    webplugin.cpp \
    utils.cpp \
    httpclientconnection.cpp \
    httpcontainers.cpp

HEADERS += webserverlib_global.h \
    weblistener.h \
    webapplication.h \
    webplugin.h \
    utils.h \
    httpclientconnection.h \
    httpcontainers.h

FORMS +=

RESOURCES +=

TRANSLATIONS +=

include($${PROJECT_ROOT}/lib.pri)
