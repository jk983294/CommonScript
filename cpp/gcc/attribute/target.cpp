#include <iostream>

using namespace std;

/**
 * multiple versions of a function, where each function is specialized for a specific target feature.
 * At runtime, the appropriate version of the function is automatically executed depending on the characteristics of
 * the execution platform.
 */

__attribute__((target("default"))) int foo() {
    // The default version of foo.
    return 0;
}
__attribute__((target("sse4.2"))) int foo() {
    // foo version for SSE4.2
    return 1;
}
__attribute__((target("arch=atom"))) int foo() {
    // foo version for the Intel ATOM processor
    return 2;
}
__attribute__((target("arch=amdfam10"))) int foo() {
    // foo version for the AMD Family 0x10 processors.
    return 3;
}

int main() {
    cout << foo() << endl;
    return 0;
}
