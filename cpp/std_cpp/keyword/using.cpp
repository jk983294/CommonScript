#include <iostream>
#include <string>
#include <vector>

using namespace std;

// prefer using over typedef for defining aliases:
typedef int (*PFI)(int);    // OK, but convoluted
using PFI2 = int (*)(int);  // OK, preferred

/*
template <typename T>
typedef int (*PFT3)(T);  // error, typedef doesn't work for template
*/

template <typename T>
using PFT4 = int (*)(T);  // OK

class Base {
public:
    Base(size_t _n) : n{_n} {}
    std::size_t size() const { return n; }

protected:
    std::size_t n;
};
class Derived : private Base {
public:
    Derived(size_t n) : Base(n) {}
    using Base::size;  // lift it to public
protected:
    using Base::n;  // lift it to protected
};

// kind of typedef
void using_as_typedef() {
    using myIntVec = std::vector<int>;
    myIntVec mvec = {1, 2, 3, 4, 5};
    for (int num : mvec) cout << num << "\t";

    cout << endl << is_same<std::vector<int>, myIntVec>::value << endl;
}

namespace Foo {
namespace Bar {
int bar_variable = 42;

namespace Meow {
void print_bar_variable() { cout << bar_variable << endl; }

class MeowObject {};
}
}
}

int main() {
    using_as_typedef();

    Derived derived(42);
    cout << derived.size() << endl;

    using Foo::Bar::bar_variable;
    ++bar_variable;
    using namespace Foo::Bar::Meow;
    print_bar_variable();
    return 0;
}
