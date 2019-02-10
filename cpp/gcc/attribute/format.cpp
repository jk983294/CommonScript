#include <iostream>

using namespace std;

void myprint(const char *format, ...) __attribute__((format(printf, 1, 2)));

void myprint(const char *format, ...) { cout << format << endl; }

int main() {
    myprint("i=%d\n", 6);
    myprint("i=%s\n", 6);
    myprint("i=%s\n", "abc");
    myprint("%s,%d,%d\n", 1, 2);
    return 0;
}
