#include <iostream>
#include "tbb/concurrent_queue.h"

using namespace tbb;
using namespace std;

int main() {
    concurrent_queue<int> cq;
    cq.push(0);
    cq.push(1);

    int x;
    while (1) {
        if (cq.try_pop(x)) {  // if no data, this will block
            cout << x << endl;
        }
        sleep(1);
    }
    return 0;
}
