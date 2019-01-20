#include <iostream>

using namespace std;

void exit_syscall() {
    __asm__(
        "movl $1, %eax;\n\t"   // SYS_exit is 1
        "xorl %ebx,%ebx;\n\t"  // Argument is in ebx, it is 0
        "int  $0x80"           // Enter kernel mode
        );
}

int main() {
    exit_syscall();
    cout << "should not see this " << endl;
    return 0;
}
