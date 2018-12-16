find_package(Qt5Core CONFIG REQUIRED)

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

#list(TRANSFORM DISTFILES
#     PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

PREPEND(DISTFILES ${CMAKE_CURRENT_SOURCE_DIR}/ ${DISTFILES})

file(COPY ${DISTFILES}
     DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
