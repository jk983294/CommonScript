#include <unistd.h>
#include <iostream>
#include "tbb/tick_count.h"

using namespace tbb;
using namespace std;

// The class tick_count provides a simple interface for measuring wall clock time.
// tick_count::now() represents the current absolute time.
// tick_count is guaranteed to be safe to use across threads.

int main() {
    tick_count t0 = tick_count::now();
    sleep(1);
    tick_count t1 = tick_count::now();
    tbb::tick_count::interval_t interval = t1 - t0;
    printf("work took %g seconds\n", interval.seconds());
    return 0;
}
