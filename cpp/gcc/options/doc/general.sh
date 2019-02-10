# file type
file.c                          # C source code
file.i                          # C preprocessed code
file.ii                         # C++ preprocessed code
file.s                          # Assembler code

gcc -c file.c                   # compile but do not link, produce object file
gcc -S file.c                   # compilation proper; do not assemble; produce assembler file
gcc -E file.c                   # preprocessing stage; do not compile; produce preprocessed C code
gcc -v file.c                   # print the commands executed to run the stages of compilation.

-fno-asm                        # do not recognize asm, inline or typeof as a keyword, use __asm__, __inline__ and __typeof__ instead
-fno-builtin                    # don’t recognize built-in functions that do not begin with ‘__builtin_’ as prefix
-fabi-version=n                 # version n of the C++ ABI. The default is version 2 G++ 3.4
-fconstexpr-depth=n             # maximum nested evaluation depth for C++11 constexpr functions, minimum specified by the standard is 512
-fdeduce-init-list              # enable deduction of a template type parameter as std::initializer_list from a brace-enclosed initializer list
-fno-elide-constructors         # g++ to call the copy constructor in all cases.
-fno-enforce-eh-specs           # Don’t generate code to check for violation of exception specifications at run time. useful for reducingcode size in production builds, much like defining ‘NDEBUG’.
-ffor-scope                     # the scope of variables declared in a for-init-statement is limited to the ‘for’ loop itself
-fnothrow-opt                   # Treat a throw() exception specification as if it were a noexcept specification to reduce or eliminate the text size overhead
-fno-pretty-templates           # error message default use void f(T) [with T = int] rather than void f(int), use this option to disable it
-fstats                         # print statistics about front-end processing at the end of the compilation
-fstrict-enums                  # optimize using the assumption that a value of enumerated type can only be one of the values of the enumeration
-fvisibility-inlines-hidden     # it massively reduces the size of the dynamic export table when the library makes heavy use of templates
-fno-weak                       # do not use weak symbol support

# Binary Compatibility
# affects code generation and runtime support for:
#     size and alignment of data types
#     layout of structured types
#     calling conventions
#     register usage conventions
#     interfaces for runtime arithmetic support
#     object file formats
#     name mangling
#     exception handling
#     invoking constructors and destructors
#     layout, alignment, and padding of classes
#     layout and alignment of virtual tables
