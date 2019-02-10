# Declaring Attributes of Functions
aligned (alignment)             # specifies a minimum alignment for the function
always_inline                   # inlines the function even if no optimization level is specified.
flatten                         # every call inside this function is inlined, if possible
cdecl                           # calling function pops off the stack space used to pass arguments
deprecated (msg)                # a warning if the function is used anywhere, int old_fn () __attribute__ ((deprecated));
fastcall                        # On the Intel 386, pass the first int argument in the register ECX and the second int argument in the register EDX. Subsequent and other typed arguments are passed on the stack.
thiscall                        # On the Intel 386, pass the first int argument in the register ECX. Subsequent and other typed arguments are passed on the stack.
stdcall                         # the called function pops off the stack space used to pass arguments
leaf                            # leaf functions are not allowed to call callback function passed to it from the current compilation unit or directly call functions exported by the unit or longjmp into the unit
noinline                        # prevents a function from being considered for inlining
nothrow                         # a function cannot throw an exception
pure                            # functions have no effects except the return value and their return value depends only on the parameters, int square (int) __attribute__ ((pure));
hot                             # the function is optimized more aggressively and on many target it is placed into special subsection of the text section so all hot functions appears close together improving locality.
cold                            # function is unlikely to be executed
regparm (number)                # regparm attribute causes the compiler to pass arguments number one to number if they are of integral type in registers EAX, EDX, and ECX
target                          # specify that a function is to be compiled with different target options, int sse3_func (void) __attribute__ ((__target__ ("sse3")));
visibility ("type")             # affects the linkage of the declaration to which it is attached.
                                # default: the declaration is visible to other modules and, in shared libraries, means that the declared entity may be overridden.
                                # hidden: Two declarations of an object with hidden linkage refer to the same object if they are in the same shared object.
                                # internal: like hidden visibility, also mean that a function is never called from another module
                                # protected: like default visibility, the declared entity cannot be overridden by another module.
weak                            # the declaration to be emitted as a weak symbol rather than a global.
weakref ("target")              # marks a declaration as a weak reference, a declaration to which weakref is attached can only be static. static int x() __attribute__ ((weakref ("y")));
