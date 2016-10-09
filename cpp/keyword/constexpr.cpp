#include <iostream>

using namespace std;

/**
 * constexpr means the value could be evaluated at compile time
 * constexpr function:
 * 1) return by value
 * 2) body only contains return expr
 */

class Base {
public:
    /**
     * constexpr constructor must have a empty function body, all in initialization list
     */
    constexpr Base(): i(0) {};
    constexpr explicit Base(int _i): i(_i) {};
    constexpr Base(const Base& b): i(b.i) {};
    Base& operator=(const Base& d){
        if (this == &d) return *this;
        i = d.i;
        return *this;
    };
public:
    int i;
};

constexpr int inc(int i) {
    return i + 1;
}

constexpr int abs(int i) {
    return i < 0 ? -i : i;
}

int main() {
    constexpr int a = inc(1);
    // constexpr int b = Inc(cin.get()); // !error
    constexpr int c = a * 2 + 1;
    constexpr Base base(1);
    enum { SIZE_X = base.i, SIZE_Y = base.i };
    return 0;
}