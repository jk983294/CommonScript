## cmake
declare build flags with TARGET_xxx()

declare dependencies with TARGET_LINK_LIBRARIES

specify what is public and what is private

### module
script.cmake file located in CMAKE_MODULE_PATH

modules can be loaded with include() command

### target & property
constructor: add_executable() / add_library()

member variables: target properties

member functions:
* get_target_property() / set_target_property()
* get_property(TARGET) / set_property(TARGET)
* target_compile_definitions()
* target_compile_features()
* target_compile_options()
* target_include_directories()
* target_link_libraries()
* target_source()

### target compile features
this tell cmake I need those feature, you figure the right CMAKE_CXX_FLAGS
```cmake
target_compile_features(Foo
    PUBLIC
        cxx_strong_enums
    PRIVATE
        cxx_lambdas
        cxx_range_for
)
```

### target link library
* PRIVATE populates non-INTERFACE_property
* INTERFACE populates INTERFACE_property
* PUBLIC populates both
* target expressed as A::B like Boost::file_system

use it to express direct dependencies, it will resolve recursively.
```cmake
target_link_libraries(Foo
    PUBLIC Bar::Bar
    PRIVATE Cow::Cow
)
```

### header only library
no build specification but pure usage requirements
```cmake
add_library(Bar INTERFACE)
target_compile_definitions(Bar INTERFACE BAR=1)

```

### export your library
```cmake
find_package(Bar 2.0 REQUIRED)
add_library(Foo INTERFACE)
target_link_libraries(Foo PRIVATE Bar::Bar)

install(TARGETS Foo EXPORT FooTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(EXPORT FooTargets
    FILE FooTargets.cmake
    NAMESPACE Foo::
    DESTINATION lib/cmake/Foo
)
```

```cmake
# how to use that find
include(CMakeFindDependencyMacro)
find_dependency(Bar 2.0)
include("${CMAKE_CURRENT_LIST_DIR}/FooTargets.cmake")

```

### variable
* lists are ';' separated strings
* cmake variables are not environment variable (unlike Makefile)
* unset variable expands to empty string

```cmake
set(hello world)
message(STATUS "hello, ${hello}")
```

### generator expression
they enable conditional linking, conditional definitions used when compiling, and conditional include directories and more.

* use $<> syntax
* evaluated during build system generation,not by command interpreter

```cmake
target_compile_definitions(foo PRIVATE "VERBOSITY=$<IF:$<CONFIG:Debug>,30,10>")
```

### custom command
* commands can be added with function() or macro()
* when new command replaces an existing one, the old one can be accessed with a _ prefix

```cmake
# function example
function(my_command input output)
    # set output to xyz and make it available to outside of this function
    # available variables within function: input output ARGC ARGV ARGN ARG0 ARG1 ARG2
    set(${output} xyz PARENT_SCOPE)
endfunction()
my_command(foo bar)     # input='foo' output='bar'
```

```cmake
# macro example
macro(my_command input output)
    # no extra scope
    # available variables within function: ${input} ${output} ${ARGC} ${ARGV} ${ARGN} ${ARG0} ${ARG1} ${ARG2} ...
    set(${output} xyz PARENT_SCOPE)
endmacro()
my_command(foo bar)     # ${output} replaced by 'bar'
```

### deprecate command
```cmake
macro(my_command)
    message(DEPRECATION "the my_command command is deprecated!")
    _my_command(${ARGV})    # dispatch to previous deprecated one
endmacro()

# deprecate variable
set(hello "hello world")

function(__deprecated_var var access)
    if(access STREQUAL "READ_ACCESS")
        message(DEPRECATION "variable '${var}' is deprecated!")
    endif()
endfunction()

# register callback when someone access hello variable
variable_watch(hello __deprecated_var)
```