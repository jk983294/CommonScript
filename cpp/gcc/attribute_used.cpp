#include <iostream>

using namespace std;

/**
 * code must be emitted for the function even if it appears that the function is not referenced.
 * This is useful, for example, when the function is referenced only in inline assembly.
 */

__attribute__((__used__)) int foo(int a, int b) { return a + b; }

int main() {
    int result = 0;

    // some inline assembly that calls foo and updates result

    std::cout << result << std::endl;
}
