#include <iostream>
#include <string>

using namespace std;

/**
 * template disambiguator, it means a function not a type
 * foo typename U is dependent on S's typename T, because unless S is being instantiated,
 * U can be instantiated afterwards
 */

template <typename T>
struct S {
    template <typename U>
    void foo() {
        cout << __PRETTY_FUNCTION__ << endl;
    }
};

template <typename T>
void bar() {
    S<T> s;
    s.template foo<T>();
}

/**
 * typename disambiguator, it means a type not a data
 * in f(T t), T::X can be referred to data X or typename struct X
 */
struct A {
    struct X {
        int data{0};
    };
    int X{1};
};
template <typename T>
void f(T t) {
    typename T::X x;
    cout << __PRETTY_FUNCTION__ << endl;
    cout << x.data << endl;
}

int main() {
    bar<int>();
    f<A>(A());
    return 0;
}
