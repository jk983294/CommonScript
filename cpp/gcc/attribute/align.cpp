#include <iostream>

using namespace std;

int x __attribute__((aligned(16))) = 1;
int y __attribute__((aligned(32))) = 2;

struct __attribute__((aligned(16))) Foo {
    int x __attribute__((aligned(16)));
    int y __attribute__((aligned(32)));
};

int main() {
    uint64_t pX = reinterpret_cast<uint64_t>(&x);
    cout << pX << " " << (pX % 64) << endl;
    uint64_t pY = reinterpret_cast<uint64_t>(&y);
    cout << pY << " " << (pY % 64) << endl;
    Foo foo;
    pX = reinterpret_cast<uint64_t>(&foo.x);
    cout << pX << " " << (pX % 64) << endl;
    pY = reinterpret_cast<uint64_t>(&foo.y);
    cout << pY << " " << (pY % 64) << endl;
    return 0;
}
