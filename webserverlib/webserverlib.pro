QT += core network
QT -= gui widgets

DBLIBS += dbnetwork

PROJECT_ROOT = ../..

DEFINES += WEBSERVERLIB_LIBRARY

SOURCES += \
    weblistener.cpp \
    webapplication.cpp \
    webplugin.cpp \
    httpclientconnection.cpp \
    httpcontainers.cpp

HEADERS += webserverlib_global.h \
    weblistener.h \
    webapplication.h \
    webplugin.h \
    httpclientconnection.h \
    httpcontainers.h

FORMS +=

RESOURCES +=

TRANSLATIONS +=

include($${PROJECT_ROOT}/lib.pri)
