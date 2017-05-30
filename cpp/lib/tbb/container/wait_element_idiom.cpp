#include <iostream>
#include "tbb/atomic.h"
#include "tbb/compat/thread"
#include "tbb/concurrent_vector.h"
#include "tbb/tbb_allocator.h"

using namespace tbb;
using namespace std;

/**
 * Waiting on an Element Idiom
 * 1. Wait until i<v.size(). Afterwards, v[i] is known to be allocated, but perhaps not constructed.
 * 2. Wait for v[i] to be constructed.
 */

class Foo {
public:
    int data;
    Foo(int data_) : data(data_) {}
};

typedef concurrent_vector<tbb::atomic<Foo*>, tbb::zero_allocator<tbb::atomic<Foo*>>> FooVector;

Foo* FetchElement(const FooVector& v, size_t i) {
    // Wait for ith element to be allocated
    while (i >= v.size()) std::this_thread::yield();
    // Wait for ith element to be constructed
    while (v[i] == NULL) std::this_thread::yield();
    return v[i];
}

int main() {
    FooVector fv;
    Foo* pf = FetchElement(fv, 5);
    cout << pf->data << endl;
    return 0;
}
