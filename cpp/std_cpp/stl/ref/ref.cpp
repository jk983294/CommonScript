#include <functional>
#include <iostream>

// helper functions that generate an object of type std::reference_wrapper

void f(int& n1, int& n2, const int& n3) {
    std::cout << "In function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    ++n1;
    ++n2;
}

int main() {
    int n1 = 1, n2 = 2, n3 = 3;
    std::function<void()> bound_f = std::bind(f, n1, std::ref(n2), std::cref(n3));  // f(1, n2, n3)
    n1 = 10;
    n2 = 11;
    n3 = 12;
    std::cout << "Before function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';  // 10 11 12
    bound_f();                                                                 // 1 11 12
    std::cout << "After function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';   // 10 12 12
    return 0;
}
