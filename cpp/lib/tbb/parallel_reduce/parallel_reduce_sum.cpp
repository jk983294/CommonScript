#include <iostream>
#include "tbb/blocked_range.h"
#include "tbb/parallel_reduce.h"

using namespace tbb;
using namespace std;

float Foo(float x) {
    // some slow work here
    return x;
}

class SumFoo {
public:
    float my_sum;
    float* my_a;

public:
    void operator()(const blocked_range<size_t>& r) {
        float* a = my_a;
        float sum = my_sum;
        size_t end = r.end();
        for (size_t i = r.begin(); i != end; ++i) sum += Foo(a[i]);
        my_sum = sum;
    }

    SumFoo(SumFoo& x, split) : my_a(x.my_a), my_sum(0) {}

    void join(const SumFoo& y) { my_sum += y.my_sum; }

    SumFoo(float a[]) : my_a(a), my_sum(0) {}
};
int main() {
    const int n = 10000;
    float a[n];
    for (size_t i = 0; i < n; ++i) a[i] = i;

    SumFoo sf(a);
    parallel_reduce(blocked_range<size_t>(0, n), sf);

    cout << sf.my_sum << endl;

    return 0;
}
