#include <iomanip>
#include <iostream>
#include <memory>

using namespace std;

// Perfect forwarding: preserves any move semantics that would have taken place
// used in template type deduction
// A& & becomes A&
// A& && becomes A&
// A&& & becomes A&
// A&& && becomes A&&

// When foo is called on an lvalue of type A, then T resolves to A&, the argument type effectively becomes A&
// When foo is called on an rvalue of type A, then T resolves to A, the argument type becomes A&&
template <class T>
void foo(T&& t) {
    cout << t << endl;
}

class Base {
public:
    int data{0};
    explicit Base(int i) : data(i) { cout << "explicit Base(int i): data(i)" << endl; }
    explicit Base(const Base& rhs) {
        cout << "Base(const Base& rhs)" << endl;
        this->data = rhs.data;
    }
    explicit Base(Base&& rhs) : data(std::move(rhs.data)) { cout << "call Base(Base&& rhs)" << endl; }
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

class MoreData {
public:
    int data1;
    int data2;
    MoreData(int d1, int d2) : data1(d1), data2(d2) {}
};

template <typename T, typename Arg>
shared_ptr<T> factory(Arg&& arg) {
    return shared_ptr<T>(new T(std::forward<Arg>(arg)));
}
template <typename T, typename... Arg>
shared_ptr<T> factory(Arg&&... arg) {
    return shared_ptr<T>(new T(std::forward<Arg>(arg)...));
}

/** forward implementation
template<class S>
S&& forward(typename remove_reference<S>::type& a) noexcept{
    return static_cast<S&&>(a);
}
*/

int main() {
    int i = 42;
    foo(i++);
    foo(++i);

    shared_ptr<Derived> d1 = factory<Derived>(i++);  // rvalue, Arg -> int&&, int&& && -> int&&
    shared_ptr<Derived> d2 = factory<Derived>(++i);  // lvalue, Arg -> int&, int& && -> int&
    cout << d1->data << endl;
    cout << d2->data << endl;

    Derived dlv(++i);
    shared_ptr<Derived> d3 =
        factory<Derived>(std::move(Derived(++i)));   // rvalue, Arg -> Derived&&, Derived&& && -> Derived&&
    shared_ptr<Derived> d4 = factory<Derived>(dlv);  // lvalue, Arg -> Derived&, Derived& && -> Derived&
    cout << d3->data << endl;
    cout << d4->data << endl;

    shared_ptr<Derived> d5 = factory<Derived, int&&>(i++);  // rvalue, Arg -> int&&, int&& && -> int&&
    shared_ptr<Derived> d6 = factory<Derived, int&>(++i);   // lvalue, Arg -> int&, int& && -> int&
    cout << d5->data << endl;
    cout << d6->data << endl;

    shared_ptr<MoreData> md = factory<MoreData>(1, 2);
    cout << md->data1 << " " << md->data2 << endl;
    return 0;
}
