#include <iostream>

using namespace std;

#define CHECK1(x, ...)       \
    if (!(x)) {              \
        printf(__VA_ARGS__); \
    }
#define CHECK2(x, ...)       \
    if ((x)) {               \
        printf(__VA_ARGS__); \
    }
#define CHECK3(...) \
    { printf(__VA_ARGS__); }

int main() {
    CHECK1(0, "here %s %s %s", "are", "some", "varargs1(1)\n");
    CHECK1(1, "here %s %s %s", "are", "some", "varargs1(2)\n");  // won't print

    CHECK2(0, "here %s %s %s", "are", "some", "varargs2(3)\n");  // won't print
    CHECK2(1, "here %s %s %s", "are", "some", "varargs2(4)\n");

    // always invokes printf in the macro
    CHECK3("here %s %s %s", "are", "some", "varargs3(5)\n");
    return 0;
}
