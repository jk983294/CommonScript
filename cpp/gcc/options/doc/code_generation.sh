-fexceptions                    # enable exception handling
-fverbose-asm                   # put extra commentary information in the generated assembly code to make it more readable
-fpic                           # generate position-independent code (PIC) suitable for use in a shared library, Such code accesses all constant addresses through a global offset table (GOT). The dynamic loader resolves the GOT entries when the program starts
-fPIC                           # emit position-independent code, suitable for dynamic linking and avoiding any limit on the size of the global offset table
-fPIE                           # similar to -fPIC, but generated position independent code can be only linked into executables
-fpack-struct[=n]               # pack all structure members
-finstrument-functions          # generate instrumentation calls for entry and exit to functions, helpful to get call graph
-ftls-model=model               # alter the thread-local storage model, default without ‘-fpic’ is initial-exec, with ‘-fpic’ the default is global-dynamic
-fvisibility=                   # default always means public, hidden means no export this symbol, ‘extern’ declarations are not affected by ‘-fvisibility’
-fstrict-volatile-bitfields     # if accesses to volatile bit-fields use a single access of the width of the field’s type, aligned to a natural alignment if possible.
