#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * volatile prevents compiler from optimizing code.
 * it used for: 1) hardware registers 2) status variables in signal handlers
 * volatile is by no means sufficient to guarantee the atomic access.
 */

int square(volatile int *ptr) { return *ptr * *ptr; }
/**
 * volatile means always read from address, not from cache
 * above function equivalent to the below function, since a may be different than b,
 * so you may not get correct square value
 */
int square_equivalent(volatile int *ptr) {
    int a, b;
    a = *ptr;
    b = *ptr;
    return a * b;
}

int main() { return 0; }
