#include <iostream>

using namespace std;

/**
 * member pointer
 * defines offset of members, combined with an object to be used
 */

class X
{
public:
    X(): i(0){}
    int f(int a, int b){
        cout << "int X::f(int a, int b)"<< endl;
        return a + b;
    }
public:
    int i;
};

class Person {
public:
    virtual void f1() const { cout << "Person::f1" << endl; }
    virtual void f2() const { cout << "Person::f2" << endl; }
    virtual void f3() const { cout << "Person::f3" << endl; }
    virtual void f4() const { cout << "Person::f4" << endl; }
    virtual void f5() const { cout << "Person::f5" << endl; }
};
class Child: public Person {
public:
    virtual void f1() const { cout << "Child::f1" << endl; }
    virtual void f2() const { cout << "Child::f2" << endl; }
    virtual void f3() const { cout << "Child::f3" << endl; }
    virtual void f4() const { cout << "Child::f4" << endl; }
    virtual void f5() const { cout << "Child::f5" << endl; }
};

void dispatch(const Person& p, int v){
    static void (Person::*lookup[])() const = { &Person::f1, &Person::f2, &Person::f3, &Person::f4, &Person::f5 };
    (p.*lookup[v])();
}

int main() {
    int X::*p = &X::i;
    int (X::*fp)(int, int) = &X::f;
    X o;
    o.*p = 6;
    cout << o.*p << endl;
    cout << (o.*fp)(1, 2) << endl;

    X *q = new X();
    q->*p = 7;
    cout << q->*p << endl;
    cout << (q->*fp)(3, 2) << endl;


    Person jk;
    dispatch(jk, 1);

    /**
     * dynamic binding still works for inheritance
     */
    Person* person = new Child;
    void (Person::*pfp)() const = &Person::f1;
    (person->*pfp)();
    return 0;
}