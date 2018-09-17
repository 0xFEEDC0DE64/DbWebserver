QT += core network
QT -= gui widgets

DBLIBS += webserverlib

PROJECT_ROOT = ../..

SOURCES += main.cpp

HEADERS +=

FORMS +=

RESOURCES +=

TRANSLATIONS +=

configinstall.path = $${OUT_PWD}/$${PROJECT_ROOT}/bin
configinstall.files = webserver.json
INSTALLS += configinstall

include($${PROJECT_ROOT}/app.pri)
