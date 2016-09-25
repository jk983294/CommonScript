#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
using namespace std;

/**
* Specialization
*/

template <typename T> struct Kitty {
    static void meow() {
        cout << "Kitty<T>::meow()" << endl;
    }
};
template <> struct Kitty<const char *> {
    static void meow() {
        cout << "Kitty<const char *>::meow()" << endl;
    }
};
template <typename X> struct Kitty<X *> {		            // partial specialization
    static void meow() {
        cout << "Kitty<X *>::meow()" << endl;
    }
};

template <typename T, typename U> struct Kitty1 {};
template <typename A, typename B> struct Kitty1<A *, B> {};
template <typename X, typename Y> struct Kitty1<X, Y *> {};

template <typename T, typename U> struct Foo {};
template <typename X> struct Foo<X, X> {};
template <typename A, typename B, typename C, typename D> struct Foo< pair<A, B>, pair<C, D> > {};

template <typename T> void meow(T){
    cout<< "meow(T)!" << endl;
}
template <> void meow(double){
    cout<< "meow(double) is a explicit specialization." << endl;
}
template <typename X> void meow(X *){
    cout<< "meow(X *) is an overloaded template, not partial specialization." << endl;
}
void meow(long){
    cout<< "meow(long) is an ordinary function." << endl;
}

template <class T> class Formatter
{
    T* m_t;
public:
    Formatter(T* t) : m_t(t) { }
    void print()
    {
        cout << *m_t << endl;
    }
};
// Specialization of template class for type char*
template<> class Formatter<char*>
{
    char** m_t;
public:
    Formatter(char** t) : m_t(t) { }
    void print()
    {
        cout << "Char value: " << **m_t << endl;
    }
};

int main() {
    Kitty<int>::meow();
    Kitty<const char *>::meow();
    Kitty<double *>::meow();

    Kitty1<int, double *> k1;
    Kitty1<int *, double> k2;
    // Kitty1<int *, double *> k3;			                // more than one partial specialization

    meow(123);
    meow(123L);
    meow(123.0);
    meow(static_cast<double *>(nullptr));

    int i = 157;
    // Use the generic template with int as the argument.
    Formatter<int>* formatter1 = new Formatter<int>(&i);
    char str[10] = "string1";
    char* str1 = str;
    // Use the specialized template.
    Formatter<char*>* formatter2 = new Formatter<char*>(&str1);
    formatter1->print();
    formatter2->print();
    return 0;
}