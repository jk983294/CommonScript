#include <iostream>
#include <typeinfo>

using namespace std;

class Base {
public:
    virtual void fun(){};
};
class Derived : public Base {};
class MoreDerived : public Derived {};

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

int main() {
    cout<<boolalpha;
    test_dynamic_cast();
    return 0;
}