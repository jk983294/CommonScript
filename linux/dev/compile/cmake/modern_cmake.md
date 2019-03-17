### old way
```cmake
cmake_minimum_required(VERSION 3.5)

ADD_SUBDIRECTORY(libtcp)

ADD_EXECUTABLE(tcp_client tcp_client.cpp)
INCLUDE_DIRECTORIES(tcp/include)
ADD_DEFINITIONS(IPV6)

TARGET_LINK_LIBRARIES(tcp_client libtcp)

# grab external projects
find_package(GTest)
find_package(Threads)
add_executable(foo foo.cpp)
target_include_directories(foo PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(foo PRIVATE ${GTEST_BOTH_LIBRARIES} Threads::Threads)
```

### modern way
```cmake
cmake_minimum_required(VERSION 3.5)

add_compile_options(-W -Wall -Werror)

add_library(mylib file1.cpp)

target_include_directories(mylib PUBLIC include)
target_include_directories(mylib PRIVATE src)

if (SOME_SETTING)
    target_compile_definitions(mylib PUBLIC WITH_SOME_SETTING)
endif()

target_link_libraries(mylib PUBLIC abc)
target_link_libraries(mylib PRIVATE xyz)

# header only libraries
add_library(myheaderlib INTERFACE)
target_include_directories(myheaderlib INTERFACE include)
target_link_libraries(myheaderlib INTERFACE BOOST::BOOST)

# grab external projects
find_package(GTest)
add_executable(foo foo.cpp)
target_link_libraries(foo GTest::GTest GTest::Main)

# anti-pattern
# global declaration
INCLUDE_DIRECTORIES(xxx)
ADD_DEFINITIONS(xxx)
LINK_LIBRARIES(xxx)
```
