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
    cout << "dynamic_cast<Base *>(p1) success " << (p != nullptr)<<endl;
    Derived* pd = dynamic_cast<Derived*>(pb);
    cout << "dynamic_cast<Derived *>(pb); success " << (pd != nullptr) << endl;

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

    const volatile double d = 5.5;
    const volatile double *dp = &d;
    *(const_cast<double *>(dp)) = 1.1;
    cout << *dp << " " << d << endl;
}

void foo(){}
/**
 * allows any pointer to be converted into any other pointer type
 */
void test_reinterpret_cast(){
    Derived *pa = new Derived();
    NonRelevant* p1 = reinterpret_cast<NonRelevant*>(pa);
    p1 = nullptr;
    delete pa;

    int (*f)();
    f = reinterpret_cast<int (*)()>(foo);
}

void test_conversion_operator(){
    int i = 6;
    float f =1.012;
    i = (int) f;                        // C style
    i = int (f);                        // C++ functional, int is a function
}

int main() {
    cout << boolalpha;
    test_dynamic_cast();                // run time
    test_static_cast();                 // compile time
    test_reinterpret_cast();            // compile time
    test_const_cast();                  // compile time
    test_conversion_operator();         // compile time
    return 0;
}