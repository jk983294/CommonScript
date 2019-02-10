#include <iostream>
#include <string>

using namespace std;

struct __attribute__((__packed__)) A {
    char a;
    int b;
    char c;
};

struct B {
    char a;
    int b;
    char c;
};

struct __attribute__((packed)) Foo {
    char x;
    int y;
};

struct Bar {
    char x;
    int y __attribute__((packed));  // choose smallest possible alignment—one byte for a variable
};

int main() {
    cout << sizeof(A) << " " << sizeof(B) << endl;
    cout << sizeof(Foo) << " " << sizeof(Bar) << endl;
    return 0;
}
