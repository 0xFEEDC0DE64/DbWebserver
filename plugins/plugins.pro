TEMPLATE = subdirs

exists(fileserverplugin/fileserverplugin.pro): SUBDIRS += fileserverplugin
exists(helloworldplugin/helloworldplugin.pro): SUBDIRS += helloworldplugin
exists(proxyplugin/proxyplugin.pro): SUBDIRS += proxyplugin
exists(seriesplugin/seriesplugin.pro): SUBDIRS += seriesplugin
exists(wifilampplugin/wifilampplugin.pro): SUBDIRS += wifilampplugin

OTHER_FILES += plugin.pri
