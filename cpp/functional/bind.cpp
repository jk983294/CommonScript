#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;
using namespace std::placeholders;

double divide(double a, double b){
    return a / b;
}

class A
{
public:
    double f(double a, double b){
        return a / b;
    }
};

int main()
{
    cout << boolalpha;
    auto b1 = bind1st(less<int>(), 10);
    cout << b1(5) << " " << b1(15) <<endl;

    auto b2 = bind2nd(less<int>(), 10);
    cout << b2(5) << " " << b2(15) <<endl;

    // bind first argument to 2.0
    function<double(double)> bf1 = bind(divide, 2.0, _1);
    cout<< bf1(5.0) << endl;
    // bind second argument to 2.0
    function<double(double)> bf = bind(divide, _1, 2.0);
    cout<< bf(5.0) << endl;

    auto fn_invert = std::bind(divide, _2, _1);                         // returns y / x
    std::cout << fn_invert(10.0, 2.0) << endl;

    // binding members:
    A a;
    auto bf2 = std::bind(&A::f, a, _1, _2);
    cout<< bf2(10.0, 20.0) << endl;                                     // same as a.f(10.0, 20.0)

    std::function<double(double)> bf3 = std::bind(&A::f, a, _1, 100.0);
    cout<< bf3(10.0) << endl;                                           // same as a.f(10.0, 100.0)
    return 0;
}