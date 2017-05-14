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
