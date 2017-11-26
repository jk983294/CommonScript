#include <iostream>
#include <string>

using namespace std;

/**
 *  an overrider does not inherit default arguments
 */

class Base {
public:
    virtual int multiply(int value, int factor = 2) = 0;
};

class Derived : public Base {
public:
    int multiply(int value, int factor = 10) override { return value * factor; }
};

int main(int argc, char const* argv[]) {
    Derived d;
    Base& b = d;

    cout << b.multiply(10) << endl;  // these two calls will call the same function but
    cout << d.multiply(10) << endl;  // with different arguments and so different results
    return 0;
}
