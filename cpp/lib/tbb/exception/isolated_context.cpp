#include <iostream>
#include <vector>
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"

using namespace tbb;
using namespace std;

bool Data[1000][1000];

int main() {
    try {
        parallel_for(0, 1000, 1, [](int i) {
            // prevent downwards propagation of cancellation into an algorithm,
            // construct an 'isolated' task_group_context
            task_group_context root(task_group_context::isolated);

            parallel_for(0, 1000, 1, [i](int j) { Data[i][j] = true; }, root);
            throw "oops";
        });
    } catch (...) {
    }
    return 0;
}
