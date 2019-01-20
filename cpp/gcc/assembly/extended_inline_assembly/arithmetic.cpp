#include <iostream>

using namespace std;

void add() {
    int foo = 10, bar = 15;
    __asm__ __volatile__("addl %%ebx,%%eax"
                         : "=a"(foo)
                         : "a"(foo), "b"(bar)  // store foo in %eax, bar in %ebx and we also want the result in %eax
                         );
    cout << "foo + bar=" << foo << endl;
}

void multiply() {
    int x = 2, five_times_x;
    __asm__("leal (%1, %1, 4), %0"
            : "=r"(five_times_x)  // output %0
            : "r"(x)              // input %1
            );
    cout << x << " * 5 = " << five_times_x << endl;
}

int main() {
    add();
    multiply();
    return 0;
}
