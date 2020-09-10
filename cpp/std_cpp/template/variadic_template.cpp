#include <algorithm>
#include <cmath>
#include <cstdarg>
#include <initializer_list>
#include <iostream>
#include <map>
#include <memory>
#include <type_traits>
#include <vector>

using namespace std;

class Foo {
public:
    int i, j, k;
    Foo(int _i, int _j, int _k) : i(_i), j(_j), k(_k){};
};

// use macro, not type safe
double stddev(int count, ...) {
    double sum = 0;
    double sum_sq = 0;
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i) {
        double num = va_arg(args, double);
        sum += num;
        sum_sq += num * num;
    }
    va_end(args);
    return std::sqrt(sum_sq / count - (sum / count) * (sum / count));
}

int sum1(std::initializer_list<int> numbers) {
    int total = 0;
    for (auto i = numbers.begin(); i != numbers.end(); i++) total += *i;
    return total;
}

template <typename T>
T sum(T v) {
    cout << __PRETTY_FUNCTION__ << endl;
    return v;
}
template <typename T, typename... Args>
T sum(T first, Args... args) {
    cout << __PRETTY_FUNCTION__ << endl;
    return first + sum(args...);
}

// peel off two arguments
template <typename T>
bool pair_comparer(T a) {  // for odd number of arguments version
    return false;
}
template <typename T>
bool pair_comparer(T a, T b) {
    return a == b;
}
template <typename T, typename... Args>
bool pair_comparer(T a, T b, Args... args) {
    return a == b && pair_comparer(args...);
}

/*
 * variadic data structures
 * a helper type that lets us access the type of the k-th element in a MyTuple
 * elem_type_holder<2, some_MyTuple_type> peels off two types from the beginning of the MyTuple,
 * and sets its type to the type of the third one
 */
template <typename... Ts>
struct MyTuple {};
template <typename T, typename... Ts>
struct MyTuple<T, Ts...> : MyTuple<Ts...> {
    MyTuple(T t, Ts... ts) : MyTuple<Ts...>(ts...), tail(t) {}
    T tail;
};
template <size_t, typename>
struct elem_type_holder;
template <typename T, typename... Ts>
struct elem_type_holder<0, MyTuple<T, Ts...>> {
    typedef T type;
};
template <size_t k, typename T, typename... Ts>
struct elem_type_holder<k, MyTuple<T, Ts...>> {
    typedef typename elem_type_holder<k - 1, MyTuple<Ts...>>::type type;
};
template <size_t k, typename... Ts>
typename std::enable_if<k == 0, typename elem_type_holder<0, MyTuple<Ts...>>::type&>::type get(MyTuple<Ts...>& t) {
    return t.tail;
}
template <size_t k, typename T, typename... Ts>
typename std::enable_if<k != 0, typename elem_type_holder<k, MyTuple<T, Ts...>>::type&>::type get(
    MyTuple<T, Ts...>& t) {
    MyTuple<Ts...>& base = t;
    return get<k - 1>(base);
}

/*
 * a function that can print out standard library containers
 * fit for vector, list, also fit for map, set
 */
template <typename T, typename U>
std::ostream& operator<<(std::ostream& out, const std::pair<T, U>& p) {
    out << "[" << p.first << ", " << p.second << "]";
    return out;
}
template <template <typename, typename> class ContainerType, typename ValueType, typename AllocType>
void print_container(const ContainerType<ValueType, AllocType>& c) {
    for (const auto& v : c) cout << v << ' ';
    cout << endl;
}
template <template <typename, typename...> class ContainerType, typename ValueType, typename... Args>
void print_container(const ContainerType<ValueType, Args...>& c) {
    for (const auto& v : c) cout << v << ' ';
    cout << endl;
}

/*
 * forward all arguments pack
 */
template <typename T, typename... Args>
unique_ptr<T> my_make_unique(Args&&... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

int func1(int a, int b = 0) {
    cout << "func1 " << a << " " << b << endl;
    return a + b;
}

int func2(int a, int b = 0, int c = 0) {
    cout << "func1 " << a << " " << b << " " << c << endl;
    return a + b + c;
}

/**
 * default argument not support, must give full list of arguments
 */
template <typename TFunc, typename... Args>
int dispatch_func(TFunc func, int a, Args... args) {
    return func(a, args...);
}

int main() {
    cout << boolalpha;
    cout << "C style variadic function: " << endl;
    cout << stddev(4, 25.0, 27.3, 26.9, 25.7) << endl;
    cout << "initializer_list variadic function: " << endl;
    cout << sum1({1, 2, 3, 4, 5}) << endl;
    cout << "template variadic function with function call expansion: " << endl;
    cout << sum(1, 2, 3, 4, 5, 7.3, 5.2) << endl;
    cout << "template variadic function: " << endl;
    cout << pair_comparer(1.5, 1.5, 2, 2, 6, 6) << endl;
    cout << pair_comparer(1.5, 1.5, 2, 2, 6, 6, 7) << endl;

    print_container(vector<int>{1, 3, 5, 7, 9});
    print_container(map<int, int>{{1, 1}, {2, 2}});

    MyTuple<double, int, const char*> t1(12.2, 42, "big");
    cout << "0th elem is " << get<0>(t1) << endl;
    cout << "1th elem is " << get<1>(t1) << endl;
    cout << "2th elem is " << get<2>(t1) << endl;
    get<1>(t1) = 103;
    cout << "1th elem is " << get<1>(t1) << endl;

    unique_ptr<Foo> f = my_make_unique<Foo>(1, 2, 3);
    cout << f->i << endl;

    cout << dispatch_func(func1, 1, 2) << endl;
    cout << dispatch_func(func2, 1, 2, 3) << endl;
    return 0;
}
