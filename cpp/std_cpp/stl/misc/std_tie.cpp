#include <iostream>
#include <string>
#include <tuple>

using namespace std;

/**
 * 1. lexicographical comparison to a struct
 * 2. unpack a tuple
 */

struct Object {
    int n;
    std::string s;
    float d;

    bool operator<(const Object& rhs) const {
        // compares n to rhs.n, then s to rhs.s, then d to rhs.d
        return std::tie(n, s, d) < std::tie(rhs.n, rhs.s, rhs.d);
    }
};

std::tuple<int, int, int> return_integers() { return {1, 2, 3}; }

int main() {
    int a, c;
    std::tie(a, std::ignore, c) = return_integers();
    cout << a << " " << c << endl;
    return 0;
}
