#include <iostream>
#include <map>
#include <vector>

using namespace std;

class widget {
public:
    vector<int> v;

public:
    widget() = default;
};

int complex_work(int x) { return x * 2; }

int main() {
    const widget x = [&] {
        widget val;                            // assume that widget has a default constructor
        for (int i = 2; i <= 10; ++i) {        // this could be some
            val.v.push_back(complex_work(i));  // arbitrarily long code
        }                                      // needed to initialize x
        return val;
    }();

    for (auto i = x.v.begin(); i != x.v.end(); ++i) cout << *i << " ";
    return 0;
}
