#include <iostream>

using namespace std;

/**
 * placement new, allow ctor to be called at a memory location
 */

class X
{
public:
    X(int _i = 0): i(_i){}
    ~X(){}
    operator int () {
        return i;
    }
public:
    int i;
};

int main() {
    X *x = new X(4);
    cout << *x << endl;
    new (x) X(8);
    cout << *x << endl;
    return 0;
}