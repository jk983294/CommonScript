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
set_target_properties(hello_lib
    PROPERTIES
    PUBLIC_HEADER "math.h"
    )

set(CMAKE_INSTALL_PREFIX /opt/version/test)

install(TARGETS hello math_lib hello_lib
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib/static
            PUBLIC_HEADER DESTINATION include
            )

install(TARGETS hello DESTINATION /opt/version/test)
