#include <iostream>

using namespace std;

inline char* my_strcpy(char* dest, const char* src) {
    int d0, d1, d2;
    __asm__ __volatile__(
        "1:\tlodsb\n\t"
        "stosb\n\t"
        "testb %%al,%%al\n\t"
        "jne 1b"
        : "=&S"(d0), "=&D"(d1), "=&a"(d2)
        : "0"(src), "1"(dest)
        : "memory");
    return dest;
}

int main() {
    const char* src = "hello world";
    char* dest = new char[64];
    my_strcpy(dest, src);
    cout << dest << endl;
    return 0;
}
