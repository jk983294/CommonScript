#include <iomanip>
#include <iostream>

using namespace std;

// a lvalue is an expression that may appear on the left or on the right hand side of an assignment
// a rvalue is an expression that can only appear on the right hand side of an assignment
// a lvalue is an expression that refers to memory location and allows us to take its address via the & operator.
// a rvalue is an expression that is not an lvalue.
//
// rvalue occur only for copy constructors and assignment operators, for the purpose of achieving move semantics
//
// void foo(X&); without void foo(X&&); --> foo can be called on l-values, but not on r-values
// void foo(X const &); without void foo(X&&); --> foo can be called on l-values and r-values
// void foo(X&&); without void foo(X&); nor void foo(X const &); --> foo can be called on r-values,
// but trying to call it on an l-value will trigger a compile error

/** std::move implementation, the purpose is to pass arguments through by reference and make it bind like an rvalue
template<class T>
typename remove_reference<T>::type&& std::move(T&& a) noexcept {
    typedef typename remove_reference<T>::type&& RvalRef;
    return static_cast<RvalRef>(a);
}
*/

void foo(int& i) { cout << "lvalue ref " << i << endl; }
void foo(int&& i) {
    // variables that are declared as rvalue reference can be lvalues or rvalues.
    // if it has a name, then it is an value. Otherwise, it is an rvalue.
    int another = i;                    // calls X(X const & rhs) not calls X(X&& rhs)
    int another1 = std::move(another);  // calls X(X&& rhs) not calls X(X const & rhs)
    cout << "rvalue ref " << another1 << endl;
}

class Base {
public:
    int data{0};
    explicit Base(int i) : data(i) { cout << "explicit Base(int i): data(i)" << endl; }
    explicit Base(const Base& rhs) {
        cout << "Base(const Base& rhs)" << endl;
        this->data = rhs.data;
    }
    Base(Base&& rhs) : data(std::move(rhs.data)) { cout << "call Base(Base&& rhs)" << endl; }
};

class Derived : public Base {
public:
    explicit Derived(int i) : Base(i) { cout << "explicit Derived(int i): Base(i)" << endl; }
    explicit Derived(const Derived& rhs) : Base(rhs) { cout << "Derived(const Derived& rhs)" << endl; }
    explicit Derived(Derived&& rhs)
        // : Base(rhs) // wrong: rhs is a lvalue
        : Base(std::move(rhs))  // good: calls Base(Base&& rhs)
    {
        cout << "Derived(Derived&& rhs)" << endl;
    }
};

int main() {
    int i = 42;
    foo(1);    // rvalue
    foo(i);    // lvalue
    foo(i++);  // rvalue
    foo(++i);  // lvalue

    Derived d1(4);
    Derived d2(d1);
    Derived d3(std::move(Derived(5)));
    cout << d2.data << endl;
    cout << d3.data << endl;
    return 0;
}
