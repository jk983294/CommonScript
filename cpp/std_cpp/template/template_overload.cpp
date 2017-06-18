#include <iostream>
#include <string>

using namespace std;

template <class T>
void f(T) {
    std::cout << "f(T)\n";
}

template <>
void f<>(int*) {
    std::cout << "f(int *) specilization\n";
}

template <class T>
void f(T*) {
    std::cout << "f(T *)\n";
}

template <>
void f<>(int*) {
    std::cout << "f(int *) another specilization\n";
}

int main() {
    int* p = 0;
    f(p);  // f(int *) another specilization
    return 0;
}
