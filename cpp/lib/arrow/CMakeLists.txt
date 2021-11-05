cmake_minimum_required (VERSION 3.0)

project(arrow_test VERSION 0.1.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/)
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)

SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_CXX_STANDARD 17)

#SET(CMAKE_CXX_FLAGS "-std=c++17 -O3 -Wall -Werror")
SET(CMAKE_CXX_FLAGS "-std=c++17 -g -Wall -Werror")

message ("cxx Flags: " ${CMAKE_CXX_FLAGS})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)

#include_directories(/opt/anaconda3/lib/python3.8/site-packages/pyarrow/include)
#link_directories(/opt/anaconda3/lib/python3.8/site-packages/pyarrow/)
find_package(Arrow REQUIRED)

add_subdirectory(src)

