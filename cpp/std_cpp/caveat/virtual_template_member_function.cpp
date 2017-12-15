#include <iostream>

using namespace std;

/**
 * Do not declare a member function template virtual. C++ does not support that.
 * If it did, vtbls could not be generated until link time.
 */

class MyBase {
public:
    template <typename T>
    virtual void print(const T& v) = 0;
};

class MyDerived : public MyBase {
public:
    template <>
    virtual void print(const int& v) {
        cout << "void MyDerived::print(const int& v)" << v << endl;
    }

    template <>
    virtual void print(const double& v) {
        cout << "void MyDerived::print(const double& v)" << v << endl;
    }
};

int main() {
    MyBase* mb = new MyDerived();
    mb->print(42);
    mb->print(42.0);
    return 0;
}
