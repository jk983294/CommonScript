#include <iostream>
#include <vector>
#include "tbb/cache_aligned_allocator.h"

using namespace tbb;
using namespace std;

/**
 * Problems of sharing arise when two threads access different words that share the same cache line.
 * The problem is that a cache line is the unit of information interchange between processor caches.
 * If one processor modifies a cache line and another processor reads the same cache line,
 * the line must be moved from one processor to the other, even if the two processors are dealing with
 * different words within the line.
 * False sharing can hurt performance because cache lines can take hundreds of clocks to move.
 */

int main() {
    std::vector<int, tbb::cache_aligned_allocator<int> > v1;

    v1.push_back(42);

    cout << v1[0] << '\n';
    return 0;
}
