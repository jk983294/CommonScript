#include <iostream>
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"

using namespace tbb;
using namespace std;

void Foo(float &x) {
    // slow work here
    x += 0.5;
}

int main() {
    const int n = 10000;
    float a[n];
    for (size_t i = 0; i < n; ++i) a[i] = i;

    // chunking is controlled by a partitioner and a grainsize
    parallel_for(blocked_range<size_t>(0, n, 2000), [=, &a](const blocked_range<size_t> &r) {
        for (size_t i = r.begin(); i != r.end(); ++i) Foo(a[i]);
    });

    cout << a[0] << endl;

    return 0;
}
