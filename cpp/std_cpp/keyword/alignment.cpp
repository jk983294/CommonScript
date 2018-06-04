#include <iostream>

using namespace std;

class NewClass {
public:
    uint32_t a;  // size: 4, alignment: 4
    // pad 4
    uint64_t b;  // size: 8, alignment: 8
    char c;      // size: 1, alignment: 1
    char d[10];  // size: 10, alignment: 1
    // pad 5
};  // size: 8 + 8 + (11 / 8 + 1 ) * 8 = 32 alignment: 8

/**
 * objects of struct S can be allocated at any address, because both S.a and S.b can be allocated at any address
 */
struct S {
    char a;  // size: 1, alignment: 1
    char b;  // size: 1, alignment: 1
};           // size: 2, alignment: 1

/**
 * objects of struct X must be allocated at 4-byte boundaries, because X.n must be allocated at 4-byte boundaries
 */
struct X {
    int n;   // size: 4, alignment: 4
    char c;  // size: 1, alignment: 1
    // three bytes padding
};  // size: 8, alignment: 4

int main() {
    cout << sizeof(NewClass) << endl;
    cout << alignof(NewClass) << endl;
    NewClass newClass;
    uint32_t* p1 = &newClass.a;
    uint64_t* p2 = &newClass.b;
    cout << (reinterpret_cast<uint64_t>(p2) - reinterpret_cast<uint64_t>(p1)) << endl;
    cout << (newClass.d - &(newClass.c)) << endl;
    cout << sizeof(S) << endl;
    cout << alignof(S) << endl;
    cout << sizeof(X) << endl;
    cout << alignof(X) << endl;
    return 0;
}
