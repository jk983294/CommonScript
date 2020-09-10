cmake_minimum_required(VERSION 3.5.1)

project(hello)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall ")
message ("cxx Flags: " ${CMAKE_CXX_FLAGS})

set(SOURCE_FILES
    main.cpp
    hello.cpp
    math.cpp
)

add_executable(hello ${SOURCE_FILES})

add_library(hello_lib STATIC hello.cpp)
set_target_properties(hello_lib
    PROPERTIES
    PUBLIC_HEADER "hello.h"
    )

add_library(math_lib SHARED math.cpp)
set_target_properties(math_lib
    PROPERTIES
    SOVERSION 1
    VERSION 1.0.0
    PUBLIC_HEADER "math.h"
    )

set(CMAKE_INSTALL_PREFIX /opt/version/test)

install(TARGETS hello math_lib hello_lib
            RUNTIME DESTINATION bin
                COMPONENT Hello_RunTime
            LIBRARY DESTINATION lib
                COMPONENT Hello_RunTime
                # NAMELINK_COMPONENT Hello_Development
            ARCHIVE DESTINATION lib/static
                COMPONENT Hello_Development
            PUBLIC_HEADER DESTINATION include
            )

install(TARGETS hello DESTINATION /opt/version/test)
