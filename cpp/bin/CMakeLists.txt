cmake_minimum_required(VERSION 3.5)

project (common_bin)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 -Wall ")
# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -Wall ")
message ("cxx Flags: " ${CMAKE_CXX_FLAGS})

file( GLOB APP_SOURCES "*.cpp")
foreach( sourcefile ${APP_SOURCES} )
    # executable name cut off .cpp
    string( REGEX REPLACE ".+/" "" executablename1 ${sourcefile} )
    string( REPLACE ".cpp" "" executablename ${executablename1} )

    message ("source files: " ${sourcefile} " executable: " ${executablename})
    add_executable( ${executablename} ${sourcefile} )
    target_link_libraries( ${executablename} pthread rt z )

    if( ${executablename} STREQUAL "pcapa" )
        target_link_libraries( ${executablename} pcap )
    endif()

    install(TARGETS ${executablename} RUNTIME DESTINATION /opt/version/latest/bin/)
endforeach( sourcefile ${APP_SOURCES} )
