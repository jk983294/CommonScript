#include <iostream>

using namespace std;

#define _syscall3(type, name, type1, arg1, type2, arg2, type3, arg3)                                   \
    type name(type1 arg1, type2 arg2, type3 arg3) {                                                    \
        long __res;                                                                                    \
        __asm__ volatile("int $0x80"                                                                   \
                         : "=a"(__res)                                                                 \
                         : "0"(__NR_##name), "b"((long)(arg1)), "c"((long)(arg2)), "d"((long)(arg3))); \
        __syscall_return(type, __res);                                                                 \
    }

void exit_syscall() {
    __asm__(
        "movl $1, %%eax;\n\t"    // SYS_exit is 1
        "xorl %%ebx,%%ebx;\n\t"  // Argument is in ebx, it is 0
        "int  $0x80"             // Enter kernel mode
        ::);
}

int main() {
    exit_syscall();
    cout << "should not see this " << endl;
    return 0;
}
