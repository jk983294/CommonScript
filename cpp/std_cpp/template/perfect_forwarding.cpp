#include <cstring>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * perfect forwarding
 */

struct foo {
    foo(char c_, string s_) : c{c_}, s{move(s_)} {}

    char c;
    string s;
};

struct bar {
    vector<foo> foos;

    template <typename... T>
    void add(T&&... t) {
        foos.emplace_back(forward<T>(t)...);
    }
};

int main() {
    bar b;
    b.add('a', "a");
    b.add(foo{'b', "b"});
    return 0;
}
