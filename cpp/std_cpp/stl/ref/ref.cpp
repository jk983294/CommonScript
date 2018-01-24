#include <functional>
#include <iostream>
#include <vector>

/**
 * helper functions that generate an object of type std::reference_wrapper
 * used as a mechanism to store references inside containers (like std::vector) which cannot normally hold references
 * also used to pass objects to std::bind or to the constructor of std::thread by reference
 */

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

    // std::vector<int&> v1{n1, n2, n3};  // cannot compile
    std::vector<std::reference_wrapper<int>> v{n1, n2, n3};
    for (int& x : v) std::cout << "value: " << x << '\n';

    std::tuple<int*> t1 = std::make_tuple(&n1);
    std::tuple<int&> t2 = std::make_tuple(std::ref(n1));
    std::tuple<int> t3 = std::make_tuple(n1);
    std::cout << *std::get<0>(t1) << " " << std::get<0>(t2) << " " << std::get<0>(t3) << '\n';
    return 0;
}
