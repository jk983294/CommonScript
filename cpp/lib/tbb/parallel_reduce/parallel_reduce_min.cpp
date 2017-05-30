#include <iostream>
#include <limits>
#include "tbb/blocked_range.h"
#include "tbb/parallel_reduce.h"

using namespace tbb;
using namespace std;

float Foo(float x) {
    // some slow work here
    return x;
}

class MinIndexFoo {
public:
    const float* const my_a;
    float value_of_min;
    long index_of_min;

public:
    void operator()(const blocked_range<size_t>& r) {
        const float* a = my_a;
        for (size_t i = r.begin(); i != r.end(); ++i) {
            float value = Foo(a[i]);
            if (value < value_of_min) {
                value_of_min = value;
                index_of_min = i;
            }
        }
    }

    MinIndexFoo(MinIndexFoo& x, tbb::split)
        : my_a(x.my_a), value_of_min(numeric_limits<float>::max()), index_of_min(-1) {}

    void join(const MinIndexFoo& y) {
        if (y.value_of_min < value_of_min) {
            value_of_min = y.value_of_min;
            index_of_min = y.index_of_min;
        }
    }

    MinIndexFoo(const float a[]) : my_a(a), value_of_min(numeric_limits<float>::max()), index_of_min(-1) {}
};

int main() {
    const int n = 10000;
    float a[n];
    for (size_t i = 0; i < n; ++i) a[i] = i;

    MinIndexFoo mif(a);
    parallel_reduce(blocked_range<size_t>(0, n), mif);

    cout << mif.index_of_min << endl;

    return 0;
}
