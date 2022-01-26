#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    // unary operator + triggers a conversion to a plain old function pointer for the lambda
    auto test = +[] { cout << "1\n"; };
    test();
    test = [] { cout << "2\n"; };
    test();
    return 0;
}