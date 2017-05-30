#include <iostream>
#include "tbb/blocked_range.h"
#include "tbb/concurrent_vector.h"

using namespace tbb;
using namespace std;

/**
 * safe: push_back, grow_by, and grow_to_at_least
 * operations on concurrent_vector are concurrency safe with respect to growing,
 * not for clearing or destroying a vector.
 * Never invoke method clear() if there are other operations in flight on the concurrent_vector
 */

int main() {
    concurrent_vector<int> cv;
    cv.push_back(0);

    int a[5] = {1, 2, 3, 4, 5};
    copy(begin(a), end(a), cv.grow_by(5));
    cv.grow_by({6, 7, 8});

    int b[3] = {9, 10, 11};
    cv.grow_by(begin(b), end(b));

    for (auto i = cv.begin(); i != cv.end(); i++) {
        cout << *i << " ";
    }
    return 0;
}
