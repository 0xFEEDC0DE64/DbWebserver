set(HEADERS
)

set(SOURCES
    main.cpp
)

set(DISTFILES
    webserver.json
)

add_executable(webserver ${HEADERS} ${SOURCES} ${DISTFILES})

target_link_libraries(webserver Qt5::Core dbcorelib webserverlib)

list(TRANSFORM DISTFILES
     PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

file(COPY ${DISTFILES}
     DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
