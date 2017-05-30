#include <iostream>
#include <type_traits>

struct A {  // non-POD type
    int avg;
    A(int a, int b) : avg((a + b) / 2) {}
};

// Obtains a POD type suitable to use as storage for an object of
// a size of at most Len bytes, aligned as specified by Align.
typedef std::aligned_storage<sizeof(A), alignof(A)>::type A_pod;

int main() {
    A_pod a, b;
    new (&a) A(10, 20);
    b = a;
    std::cout << reinterpret_cast<A&>(b).avg << std::endl;
    return 0;
}
