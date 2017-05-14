#include <functional>
#include <iostream>
#include <memory>
#include <random>

using namespace std::placeholders;

void f(int n1, int n2, int n3, const int& n4, int n5) {
    std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}

int g(int n1) { return n1; }

struct Foo {
    void print_sum(int n1, int n2) { std::cout << n1 + n2 << '\n'; }
    int data = 10;
};

int main() {
    int n = 7;
    auto f1 = std::bind(f, _2, _1, 42, std::cref(n), n);  // _1, _2 represent future arguments which passed to f1
    n = 10;
    f1(1, 2);  // makes a call to f(2, 1, 42, n, 7)

    // nested bind subexpressions share the placeholders
    auto f2 = std::bind(f, _3, std::bind(g, _3), _3, 4, 5);
    f2(10, 11, 12);  // makes a call to f(12, g(12), 12, 4, 5)

    // bind to a pointer to member function
    Foo foo;
    auto f3 = std::bind(&Foo::print_sum, &foo, 95, _1);
    f3(5);  // foo.print_sum(95, 5)

    // bind to a pointer to data member
    auto f4 = std::bind(&Foo::data, _1);
    std::cout << f4(foo) << '\n';  // foo.data

    // smart pointers can be used to call members of the referenced objects, too
    std::cout << f4(std::make_shared<Foo>(foo)) << '\n';

    // common use case: binding a RNG with a distribution
    std::default_random_engine e;
    std::uniform_int_distribution<> d(0, 10);
    std::function<int()> rnd = std::bind(d, e);  // a copy of e is stored in rnd
    for (int n = 0; n < 10; ++n) std::cout << rnd() << ' ';
    std::cout << '\n';
    return 0;
}
