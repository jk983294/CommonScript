#include <iostream>

using namespace std;

struct Base {
    virtual ~Base() {}
};
struct Derived : Base {
    void df() { std::cout << "df()\n"; }
};

template <typename T>
auto get_value(T t) {
    if constexpr (std::is_pointer_v<T>)
        return *t;  // deduces return type to int for T = int*
    else
        return t;  // deduces return type to int for T = int
}

void if_init_block() {
    Base* bp1 = new Base;
    Base* bp2 = new Derived;

    if (Derived* p = dynamic_cast<Derived*>(bp1))  // cast fails, returns nullptr
        p->df();                                   // not executed

    if (auto p = dynamic_cast<Derived*>(bp2))  // cast succeeds
        p->df();                               // executed
}

void if_constexpr() {
    int v = 42;
    int* pv = &v;
    cout << get_value(v) << endl;
    cout << get_value(pv) << endl;
}

int main() {
    if_init_block();
    if_constexpr();
}
