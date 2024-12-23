#include <iostream>

using namespace std;

template <class T>
struct Base {
    void interface() { static_cast<T *>(this)->implementation(); }

    static void static_func() { T::static_sub_func(); }
};

struct Derived1 : Base<Derived1> {
    void implementation() { cout << "Derived1::implementation()" << endl; }

    static void static_sub_func() { cout << "Derived1::static_sub_func()" << endl; }
};

struct Derived2 : Base<Derived2> {
    void implementation() { cout << "Derived2::implementation()" << endl; }

    static void static_sub_func() { cout << "Derived2::static_sub_func()" << endl; }
};

int main() {
    Base<Derived1> *derived1 = new Derived1;
    derived1->interface();
    derived1->static_func();

    Base<Derived2> *derived2 = new Derived2;
    derived2->interface();
    derived2->static_func();
    return 0;
}
