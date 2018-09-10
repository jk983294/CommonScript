#include <iostream>

using namespace std;

/**
 * explicit specializations have to be at namespace scope
 * below won't compile:
 * struct O {
 *   int a{-1};
 *   int b{-1};
 *
 *   template <typename T> void set(int data){ }
 *   template <> void set<A>(int data){ a = data; }
 *   template <> void set<B>(int data){ a = data; }
 * };
 *
 * workaround
 * (1) use template <typename T, typename std::enable_if<std::is_same<YourType, T>::value>::type* = nullptr>
 * (2) use overload, and one template to dispatch with identity trait
 * (3) move specializations of the member templates outside of the class body
 */

struct A {};
struct B {};

struct O {
    int a{-1};
    int b{-1};

    template <typename T, typename std::enable_if<std::is_same<A, T>::value>::type* = nullptr>
    void set(int data) {
        a = data;
    }
    template <typename T, typename std::enable_if<std::is_same<B, T>::value>::type* = nullptr>
    void set(int data) {
        b = data;
    }
};

template <typename T>
struct identity {
    typedef T type;
};

struct P {
    int a{-1};
    int b{-1};

    template <typename T>
    void set(int data) {
        _set(data, identity<T>());
    }

    // overload
    void _set(int data, identity<A>) { a = data; }
    void _set(int data, identity<B>) { b = data; }
};

struct Q {
    int a{-1};
    int b{-1};

    template <typename T>
    void set(int data) {}
};

template <>
inline void Q::set<A>(int data) {
    a = data;
}
template <>
inline void Q::set<B>(int data) {
    b = data;
}

int main() {
    O o;
    o.set<A>(1);
    o.set<B>(2);
    cout << o.a << " " << o.b << endl;

    P p;
    p.set<A>(4);
    p.set<B>(2);
    cout << p.a << " " << p.b << endl;

    Q q;
    q.set<A>(4);
    q.set<B>(2);
    cout << q.a << " " << q.b << endl;
    return 0;
}
