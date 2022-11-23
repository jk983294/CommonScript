#include <iostream>

using namespace std;

/**
 * macro substitution
 */
#define MIN(a, b) ((a) < (b) ? (a) : (b))
void macro_substitution_bug() {
    int x = 5, y = 7;
    cout << "min is " << MIN(x, y) << endl;
    // ((++x) < (++y) ? (++x) : (++y))
    cout << "min is " << MIN(++x, ++y) << endl;
}

/**
 * inline
 */
inline int MIN1(int a, int b) { return a < b ? a : b; }
void inline_demo() {
    int x = 5, y = 7;
    cout << "min is " << MIN1(x, y) << endl;
    cout << "min is " << MIN1(++x, ++y) << endl;
}

class Foo {
public:
    Foo() { ++num_instances; }
    ~Foo() { --num_instances; }
    inline static int num_instances = 0;  // no need init in .cpp file, it all refer to the same int object.
};

int main() {
    cout << boolalpha;
    macro_substitution_bug();
    inline_demo();
    Foo::num_instances++;
    cout << Foo::num_instances << endl;
    return 0;
}