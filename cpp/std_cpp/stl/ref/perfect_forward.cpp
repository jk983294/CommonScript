#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

using namespace std;

/**
 * forwarding reference
 * reference collapsing
 * & & -> &
 * && & -> &
 * & && -> &
 * && && -> &&
 *
 * overload priority:
 * X&& bind to X&&, T&&, const X&&, const T&&, const X&
 * const X&& bind to const X&&, const T&&, T&&, const X&
 */

template <typename T>
void foo(T&&) {
    cout << "foo(T&&)" << endl;
}

struct Obj {};

template <typename T>
struct A1 {
    A1(T&& t) : obj(std::move(t)) {}  // T is class type, T&& is rref
    Obj obj;
};

struct A2 {
    template <typename T>
    A2(T&& t) : obj(std::forward(t)) {}  // T&& is forward ref
    Obj obj;
};

template <typename T>
void bar(T&&) {
    using NoRef = std::remove_reference_t<T>;
    if constexpr (std::is_integral<NoRef>::value) {  // can not use T directly
        cout << "int" << endl;
    } else {
        cout << "non int" << endl;
    }
}

int main() {
    int x{};
    const int y{};
    foo(x);      // foo(int& &&)
    foo(int{});  // foo(int&&)

    bar(x);
    bar(int{});
    bar(y);
    return 0;
}
