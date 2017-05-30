#include <iostream>
#include <utility>  // std::forward

// returns an rvalue reference to arg if arg is not an lvalue reference.

void overloaded(const int& x) { std::cout << "[lvalue]"; }
void overloaded(int&& x) { std::cout << "[rvalue]"; }

template <class T>
void fn(T&& x) {                     // signature is rvalue reference
    overloaded(x);                   // always an lvalue
    overloaded(std::forward<T>(x));  // rvalue if original argument is rvalue
}

int main() {
    int a;

    std::cout << "calling fn with lvalue: ";
    fn(a);  // [lvalue][lvalue]
    std::cout << '\n';

    std::cout << "calling fn with rvalue: ";
    fn(0);  // [lvalue][rvalue]
    std::cout << '\n';

    return 0;
}
