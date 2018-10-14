set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plugins/webserver)

add_custom_target(webserver-plugins)

add_subdirectory(fileserverplugin)
add_subdirectory(helloworldplugin)
add_subdirectory(proxyplugin)
add_subdirectory(seriesplugin)
add_subdirectory(wifilampplugin)
