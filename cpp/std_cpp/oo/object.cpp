#include <iostream>

using namespace std;

class Base {
public:
    Base(): i(0) {};                                                // init order is declaration order
    explicit Base(int _i): i(_i) {};                                // avoid implicit conversion from int to Base
    Base(const Base& b): i(b.i) {};
    virtual ~Base(){};                                              // if no virtual, only base destructor called
    Base& operator=(const Base& d){
        if (this == &d) return *this;
        i = d.i;
        return *this;
    };
    static int getSome(){
        return some;
    };
    virtual void f(){
        cout << "Base::f()" <<endl;
    };
    virtual void g() final {                                        // final cannot override
        cout << "Base::g()" <<endl;
    };
public:
    int i {0};                                                      // init before constructor
    static int some;
    static const int max = 100;
};

class Derived : public Base {
public:
    Derived(): Base(0), j(0) {};
    explicit Derived(int _i): Base(_i), j(_i){};
    explicit Derived(int _i, int _j): Base(_i), j(_j){};
    Derived(const Derived& d): Base(d), j(d.j){};
    Derived& operator=(const Derived& d){
        if (this == &d) return *this;
        Base::operator=(d);
        j = d.j;
        return *this;
    };
    void f() override {
        cout << "Derived::f()" <<endl;
    }
    friend ostream& operator<<(ostream& s, const Derived);
    using Base::Base;                                               // lift base constructor into derived class scope
public:
    int j;
};
ostream& operator<<(ostream& s, const Derived n){
    s << "Number [ " << n.i << " , " << n.j << " ]";
    return s;
}

int Base::some = 10;

int main()
{
    Derived n(3);
    cout << n << endl;
    cout << Base::max << endl;
    cout << Base::some << " " << Base::getSome() << endl;
    n.f();
    return 0;
}