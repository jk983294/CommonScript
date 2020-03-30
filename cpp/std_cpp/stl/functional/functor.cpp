#include <iostream>
#include <string>
#include <functional>

using namespace std;

template<typename T>
struct fancy_op : public binary_function<T, T, T>
{
    T operator()(const T& __x, const T& __y) const
    { return __x + __y + 42; }
};

template<typename T>
struct identity : public unary_function<T, T>
{
    T operator()(const T& __x) const
    { return __x; }
};

int main()
{
    cout << std::plus<int>()(1, 2) << endl;
    cout << std::minus<int>()(1, 2) << endl;
    cout << std::multiplies<int>()(1, 2) << endl;
    cout << std::divides<float>()(1, 2) << endl;
    cout << std::modulus<int>()(3, 2) << endl;
    cout << std::negate<int>()(3) << endl;

    cout << fancy_op<int>()(0, 0) << endl;
    cout << identity<int>()(3) << endl;
    return 0;
}
