#include <iostream>

using namespace std;


/**
 * diamond inheritance
 * virtual causes members of base class to appear once
 */
class A {
public:
    A(int _x): x(_x){};
    int x;
};
class B : virtual public A {
public:
    B(int _x): A(_x){};
};
class C : virtual public A {
public:
    C(int _x): A(_x){};
};
class D : public B, public C {
public:
    D(int _x): A(_x + 1), B(_x + 2), C(_x + 3){};
};


int main()
{
    D d(3);
    cout << d.A::x << endl;
    cout << d.B::x << endl;
    cout << d.C::x << endl;
    cout << d.D::x << endl;
    return 0;
}