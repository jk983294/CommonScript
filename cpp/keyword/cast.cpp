#include <iostream>
#include <typeinfo>

using namespace std;

class Base {
public:
    virtual void fun(){};
};
class Derived : public Base {};
class NonRelevant {};

void test_dynamic_cast()
{
    Base* pb = new Base();
    Derived* p1 = new Derived();

    Base* p = dynamic_cast<Base*>(p1);
    cout << "dynamic_cast<Base *>(p1) success " << (p != NULL)<<endl;
    Derived* pd = dynamic_cast<Derived*>(pb);
    cout << "dynamic_cast<Derived *>(pb); success " << (pd != NULL) << endl;

    delete pb;
    delete p1;
    try {
        Base obb;
        Derived obd;
        Base& ob1 = dynamic_cast<Base&>(obd);
        Derived& ob2 = dynamic_cast<Derived&>(obb);
    } catch(bad_cast e) {
        cout<< "catch bad_cast exception " << e.what() << endl;
    }
}

void test_static_cast(){
    float f =1.012;
    int i = static_cast<int>(f);
}

void test_const_cast(){
    const NonRelevant *a = new NonRelevant;
    NonRelevant *b = const_cast<NonRelevant *>(a);
}

void test_reinterpret_cast(){
    Derived *pa = new Derived();
    NonRelevant* p1 = reinterpret_cast<NonRelevant*>(pa);
    p1 = nullptr;
    delete pa;
}

int main() {
    cout << boolalpha;
    test_dynamic_cast();
    test_static_cast();
    test_reinterpret_cast();
    test_const_cast();
    return 0;
}