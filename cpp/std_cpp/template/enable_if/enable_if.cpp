#include <iostream>
#include <type_traits>
#include <vector>

using namespace std;

/**
 * SFINAE (substitution-failure-is-not-an-error) principle:
 * if an invalid argument or return type is formed during the instantiation of a function template,
 * the instantiation is removed from the overload resolution set instead of causing a compilation error.
 *
 * ways to use enable_if:
 * 1) add enable_if on return value
 * template <class T> typename enable_if<is_arithmetic<T>::value, T>::type  foo(T t) {}
 * 2) add enable_if as an extra default argument
 * template <class T> T foo(T t, typename enable_if<is_arithmetic<T>::value >::type* dummy = nullptr){}
 * 3) extra template argument
 * template <class T, typename std::enable_if_t<std::is_integral<T>::value>* = nullptr> void do_stuff(T& t){}
 * template <class T, typename std::enable_if_t<std::is_class<T>::value>* = nullptr> void do_stuff(T& t){}
 */

template <typename T>
struct has_iterator {
    template <typename U>
    static char test(typename U::iterator* x);

    template <typename U>
    static long test(U* x);

    static const bool value = sizeof(test<T>(nullptr)) == 1;
};

template <typename T, typename std::enable_if_t<!has_iterator<T>::value>* = nullptr>
void show(const T& x) {
    cout << x << endl;
}

template <typename T, typename std::enable_if_t<has_iterator<T>::value>* = nullptr>
void show(const T& x) {
    for (auto& i : x) cout << i << " ";
    cout << endl;
}

int main() {
    int a = 128;
    vector<string> s = {"hello", "wold", "kun"};

    show(a);
    show(s);
    return 0;
}
