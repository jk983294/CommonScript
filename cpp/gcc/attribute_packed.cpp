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

int main() {
    cout << sizeof(A) << " " << sizeof(B) << endl;
    return 0;
}
