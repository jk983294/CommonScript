#include <iostream>

using namespace std;

/**
 * string concatenation operator, also known as he token-pasting operator.
 * ## takes the string value of a parameter and concatenates it with another string
 */

#define DECLARE_MY_VAR(type) type my_##type

struct X {
    DECLARE_MY_VAR(int);
    DECLARE_MY_VAR(double);
};

int main() {
    X x;
    x.my_int = 1;
    x.my_double = 4.2;

    cout << x.my_int << " " << x.my_double << endl;
    return 0;
}
