#include <iostream>

using namespace std;

void bit_set(int x, int pos) {
    cout << x << endl;
    __asm__ __volatile__("btsl %1, %0"
                         : "=m"(x)
                         : "Ir"(pos)
                         : "cc"  // condition codes will be changed, we are adding "cc" to clobber list
                         );
    cout << x << endl;
}

void bit_clear(int x, int pos) {
    cout << x << endl;
    __asm__ __volatile__("btrl %1, %0"
                         : "=m"(x)
                         : "Ir"(pos)
                         : "cc"  // condition codes will be changed, we are adding "cc" to clobber list
                         );
    cout << x << endl;
}

int main() {
    bit_set(0x0F, 4);
    bit_clear(0x0F, 3);
    return 0;
}
