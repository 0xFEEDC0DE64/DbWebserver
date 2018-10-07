set(HEADERS
)

set(SOURCES
    main.cpp
)

add_executable(webserver ${HEADERS} ${SOURCES})

target_link_libraries(webserver Qt5::Core dbcorelib webserverlib)
