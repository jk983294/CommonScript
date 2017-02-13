#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int square(volatile int *ptr){
    return *ptr * *ptr;
}
/**
 * volatile means always read from address, not from cache
 * above function equivalent to the below function, since a may be different than b,
 * so you may not get correct square value
 */
int square_equivalent(volatile int *ptr){
    int a,b;
    a = *ptr;
    b = *ptr;
    return a * b;
}

int main() {

    return 0;
}