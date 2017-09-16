#include <iostream>

using namespace std;

void foo() {
    int x = 42;
    int* crash = NULL;
    int y = x + 1;
    *crash = y;
}

int main(int argc, char const* argv[]) {
    foo();
    return 0;
}
