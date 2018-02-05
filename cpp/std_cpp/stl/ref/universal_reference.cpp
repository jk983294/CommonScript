#include <iostream>
#include <utility>  // std::forward

/**
 * function template parameter has type T&&
 * an object is declared using auto&&
 * universal references is rvalue references if they’re initialized with rvalues.
 * they are lvalue references if they’re initialized with lvalues.
 */

void process(const int& x) { std::cout << "lvalue " << x << '\n'; }
void process(int&& x) { std::cout << "rvalue " << x << '\n'; }

template <class T>
void log_and_process(T&& x) {
    /**
     * although x's signature is rvalue reference,
     * but it actually an lvalue in this function call
     * without perfect forwarding, it will always call lvalue version of process
     */
    std::cout << "log_and_process with " << x << '\n';
    process(std::forward<T>(x));
}

int main() {
    int a = 42;

    log_and_process(a);  // lvalue 42

    log_and_process(std::move(a));  // rvalue 42
    return 0;
}
