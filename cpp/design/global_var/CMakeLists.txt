cmake_minimum_required(VERSION 3.16)
project(cpp)

set(CMAKE_CXX_STANDARD 17)

#SET(CMAKE_CXX_FLAGS "-std=c++17 -O3 -s")
#SET(CMAKE_CXX_FLAGS "-std=c++17 -O3 -s -Wall -Werror")
SET(CMAKE_CXX_FLAGS "-std=c++17 -g -Wall -Werror")

include_directories(.)

add_library( base SHARED "FactoryObject.cpp" )
set_property(TARGET base PROPERTY POSITION_INDEPENDENT_CODE ON)

add_library( shared1 SHARED "shared1.cpp" )
set_property(TARGET shared1 PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries( shared1 base )

add_library( shared2 SHARED "shared2.cpp" )
set_property(TARGET shared2 PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries( shared2 base )


add_executable(cpp main.cpp)
target_link_libraries(cpp base pthread dl)
