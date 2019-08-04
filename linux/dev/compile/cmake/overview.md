### Object Libraries
It defines a non-archival collection of object files resulting from compiling the given source files. The object files collection can be used as source inputs to other targets
```cmake
add_library(archive OBJECT archive.cpp zip.cpp lzma.cpp)
add_library(archiveExtras STATIC $<TARGET_OBJECTS:archive> extras.cpp)
add_executable(test_exe $<TARGET_OBJECTS:archive> test.cpp)
```

### build per target
* target_include_directories() populate the INCLUDE_DIRECTORIES and INTERFACE_INCLUDE_DIRECTORIES
* target_compile_definitions() populate COMPILE_DEFINITIONS and INTERFACE_COMPILE_DEFINITIONS
* target_compile_options() populate COMPILE_OPTIONS and INTERFACE_COMPILE_OPTIONS

### Target Properties
* INCLUDE_DIRECTORIES added to the compile line with -I
* COMPILE_DEFINITIONS are prefixed with -D

### Include Directories
```cmake
add_library(lib1 lib1.cpp)
target_include_directories(lib1 PRIVATE
  /absolute/path
  relative/path
)
```
### Runtime Output Artifacts
* RUNTIME_OUTPUT_DIRECTORY
* RUNTIME_OUTPUT_NAME

### Library Output Artifacts
* LIBRARY_OUTPUT_DIRECTORY
* LIBRARY_OUTPUT_NAME

### Archive Output Artifacts
* ARCHIVE_OUTPUT_DIRECTORY
* ARCHIVE_OUTPUT_NAME
