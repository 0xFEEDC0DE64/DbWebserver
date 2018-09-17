TEMPLATE = subdirs

SUBDIRS += webserver \
           webserverlib \
           plugins

webserver.depends += webserverlib
plugins.depends += webserverlib
