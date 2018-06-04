#include <iostream>

using namespace std;

template <class T>
void f(T) {
    std::cout << "f(T)\n";
}

template <>
void f<>(int*) {
    std::cout << "f(int *) specilization\n";
}

/**
 * !!! this is an overload, function templates can't be partially specialized
 * function templates do support fully specialized
 */
template <class T>
void f(T*) {
    std::cout << "f(T *)\n";
}

template <>
void f<>(int*) {
    std::cout << "f(int *) another specilization\n";
}

int main() {
    /**
     * the last specilization will be picked
     * if template <> void f<>(int*) not defined, it will pick template <class T> void f(T*)
     */
    int* p = 0;
    f(p);  // f(int *) another specilization

    int x = 42;
    f(x);  // f(T)
    return 0;
}
