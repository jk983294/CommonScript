#include <iostream>

using namespace std;

/**
 * code must be emitted for the function even if it appears that the function is not referenced.
 * This is useful, for example, when the function is referenced only in inline assembly.
 */

__attribute__((always_inline)) inline int foo(int a, int b) { return a + b; }

int main() {
    int result = foo(21, 21);
    std::cout << result << std::endl;
}
