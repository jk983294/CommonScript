#include <iostream>
#include <string>
#include <functional>

using namespace std;

float my_add(float x, float y) { return x + y; }
float my_minus(float x, float y) { return x - y; }

template <typename T>
T my_template_add(T x, T y) { return x + y; }

/**
 * TFunctor is a object
 */
template <typename T, typename TFunctor>
struct MyObject1 {
    T a;
    T b;
    TFunctor f;
    MyObject1(T a_, T b_, const TFunctor& f_): a{a_}, b{b_}, f{f_} {}

    T calc() {
        return f(a, b);
    }
};

/**
 * TFunc is function pointer
 */
template <typename T, typename TFunc>
struct MyObject2 {
    T a;
    T b;
    function<TFunc> f;
    MyObject2(T a_, T b_, TFunc f_): a{a_}, b{b_}, f{f_} {}

    T calc() {
        return f(a, b);
    }
};

int main()
{
    MyObject1<float, function<float (float, float)>> object1_0{1, 2, my_add};
    MyObject1<float, function<float (float, float)>> object1_1{1, 2, my_minus};
    MyObject1<float, std::plus<float>> object1_2{1, 2, std::plus<float>()};
    cout << object1_0.calc() << endl;
    cout << object1_1.calc() << endl;
    cout << object1_2.calc() << endl;

    MyObject2<float, decltype(my_add)> object2_0{1, 2, my_add};
    MyObject2<float, decltype(my_template_add<float>)> object2_1{1, 2, my_template_add<float>};
    cout << object2_0.calc() << endl;
    cout << object2_1.calc() << endl;
    return 0;
}
