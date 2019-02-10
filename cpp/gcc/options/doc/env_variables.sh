# Environment Variables Affecting GCC
COMPILER_PATH                   # like PATH. GCC tries the directories specified when searching for subprograms
LIBRARY_PATH                    # like PATH. GCC tries the directories specified when searching for special linker files, but directories specified with ‘-L’ come first
CPATH                           # if CPATH=/special/include, that has the same effect as ‘-I. -I/special/include’
C_INCLUDE_PATH
CPLUS_INCLUDE_PATH              # look for header files, CPATH as if specified with ‘-I’, but after any paths given with ‘-I’ options on the command line
