#include <iostream>
#include <stdexcept>

using namespace std;

/**
 * noexcept operator performs a compile-time check that returns true if an expression is declared to not throw any exceptions.
 * a function template's noexcept specifier can declare that the function will throw exceptions for some types but not others.
 */

void foo() noexcept {
    cout << "hey" << endl;
}
void foo1() noexcept(true) {}
void foo2() throw() {
    cout << "hey" << endl;
}
void bar() throw(overflow_error) {
    cout << "hey" << endl;
}
void bar1() noexcept( noexcept(bar()) ) {       // bar1 has the same except state
    cout << "hey" << endl;
}

template <class T>
void f() noexcept(noexcept(T())) {
}


void baz() noexcept {
    throw 42;
}

int main(){
    cout << boolalpha;
    cout << noexcept(foo()) << endl;
    cout << noexcept(foo1()) << endl;
    cout << noexcept(foo2()) << endl;
    cout << noexcept(bar()) << endl;
    cout << noexcept(bar1()) << endl;
    cout << noexcept(baz()) << endl;
    cout << noexcept(f<int>()) << endl;


    baz();                                      // compiles, but at runtime this calls std::terminate
    return 0;
}