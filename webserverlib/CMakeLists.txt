find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)

set(HEADERS
    httpclientconnection.h
    httpexception.h
    httpnotfoundexception.h
    httprequest.h
    httpresponse.h
    webapplication.h
    weblistener.h
    webplugin.h
    webserver.h
    webserverlib_global.h
)

set(SOURCES
    httpclientconnection.cpp
    httpexception.cpp
    httpnotfoundexception.cpp
    httprequest.cpp
    httpresponse.cpp
    webapplication.cpp
    weblistener.cpp
    webplugin.cpp
    webserver.cpp
)

add_library(webserverlib SHARED ${HEADERS} ${SOURCES})

target_compile_definitions(webserverlib PRIVATE WEBSERVERLIB_LIBRARY)

target_link_libraries(webserverlib Qt5::Core Qt5::Network dbnetworklib)

target_include_directories(webserverlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
