#include <iostream>
#include <vector>
#include "tbb/spin_rw_mutex.h"

using namespace tbb;
using namespace std;

/*
 * It is possible to upgrade a reader lock to a writer lock
 * For symmetry, there is a corresponding method downgrade_to_reader,
 * though in practice there are few reasons to use it.
 */

std::vector<string> v;
typedef spin_rw_mutex MyVectorMutexType;
MyVectorMutexType mutex;

void AddKeyIfMissing(const string& key) {
    // Obtain a reader lock on mutex
    MyVectorMutexType::scoped_lock lock(mutex, /*is_writer=*/false);
    size_t n = v.size();
    for (size_t i = 0; i < n; ++i)
        if (v[i] == key) return;
    if (!lock.upgrade_to_writer()) {
        // Check again to see if key was added while lock was temporarily released
        for (size_t i = n; i < v.size(); ++i) {
            if (v[i] == key) return;
        }
    }
    v.push_back(key);
}

int main() {
    AddKeyIfMissing("jk");
    return 0;
}
