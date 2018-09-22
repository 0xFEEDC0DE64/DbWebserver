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
    httprequest.cpp \
    httpresponse.cpp \
    webserver.cpp

HEADERS += webserverlib_global.h \
    weblistener.h \
    webapplication.h \
    webplugin.h \
    httpclientconnection.h \
    httprequest.h \
    httpresponse.h \
    webserver.h

FORMS +=

RESOURCES +=

TRANSLATIONS +=

include($${PROJECT_ROOT}/lib.pri)
