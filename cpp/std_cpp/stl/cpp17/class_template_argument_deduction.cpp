#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

/**
 * class template argument deduction (CTAD)
 * compiler will deduce the template arguments from the type of the initializer
 */

template <class T>
struct A {
    A(T, T) {}
};

int main() {
    std::pair p(2, 4.5);                        // deduces to std::pair<int, double> p(2, 4.5);
    std::tuple t = std::make_tuple(4, 3, 2.5);  // same as auto t = std::make_tuple(4, 3, 2.5);
    std::tuple t1(4, 3, 2.5);                   // same as auto t = std::make_tuple(4, 3, 2.5);
    std::less l;                                // same as std::less<void> l;
    auto y = new A{1, 2};                       // allocated type is A<int>

    cout << p.first << " " << p.second << endl;
    cout << std::get<0>(t) << " " << std::get<1>(t) << endl;
    return 0;
}
