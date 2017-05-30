#include <iostream>
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"

using namespace tbb;
using namespace std;

void Foo(float &x) {
    // slow work here
    x += 0.5;
}

class ApplyFoo {
    float *const my_a;

public:
    void operator()(const blocked_range<size_t> &r) const {
        float *a = my_a;
        for (size_t i = r.begin(); i != r.end(); ++i) Foo(a[i]);
    }
    ApplyFoo(float a[]) : my_a(a) {}
};

int main() {
    const int n = 10000;
    float a[n];
    for (size_t i = 0; i < n; ++i) a[i] = i;
    parallel_for(blocked_range<size_t>(0, n), ApplyFoo(a));

    cout << a[0] << endl;

    return 0;
}
