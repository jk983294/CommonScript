#include <iostream>
#include <vector>
#include "tbb/scalable_allocator.h"

using namespace tbb;
using namespace std;

/**
 * Problems of scalability arise when using memory allocators originally designed for serial programs,
 * on threads that might have to compete for a single shared pool in a way that
 * allows only one thread to allocate at a time.
 * Use the scalable_allocator<T> template to avoid scalability bottlenecks.
 * This template can improve the performance of programs that rapidly allocate and free memory.
 */

int main() {
    std::vector<int, tbb::scalable_allocator<int> > v1;

    v1.push_back(42);

    cout << v1[0] << '\n';
    return 0;
}
