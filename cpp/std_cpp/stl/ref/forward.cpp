#include <iostream>
#include <utility>  // std::forward

/**
 * std::move performs an unconditional cast to an rvalue. In and of itself, it does not move anything
 * std::forward is a conditional cast:
 * it casts to an rvalue only if its argument was initialized with an rvalue
 * Neither std::move nor std::forward do anything at runtime.
 */

void process(int& x) { std::cout << "lvalue int& " << x << '\n'; }
void process(const int& x) { std::cout << "lvalue const int& " << x << '\n'; }
void process(int&& x) { std::cout << "rvalue " << x << '\n'; }

template <class T>
void log_and_process(T&& x) {
    /**
     * x is universal reference, feed it to perfect forwarding
     */
    std::cout << "log_and_process with " << x << '\n';
    process(std::forward<T>(x));
}

int main() {
    int a = 42;
    const int b = 43;
    log_and_process(b);
    log_and_process(a);  // lvalue 42
    log_and_process(std::move(a));  // rvalue 42
    return 0;
}
