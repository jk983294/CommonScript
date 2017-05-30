#include <iostream>
#include <vector>
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"

using namespace tbb;
using namespace std;

// Exceptions propagate upwards. Cancellation propagates downwards.

vector<int> Data;

struct Update {
    void operator()(const blocked_range<int>& r) const {
        for (int i = r.begin(); i != r.end(); ++i)
            if ((size_t)i < Data.size()) {
                ++Data[i];
            } else {
                // Cancel related tasks.
                if (task::self().cancel_group_execution()) cout << "Index " << i << " caused cancellation\n";
                return;
            }
    }
};

int main() {
    Data.resize(1000);
    parallel_for(blocked_range<int>(0, 2000), Update());
    return 0;
}
