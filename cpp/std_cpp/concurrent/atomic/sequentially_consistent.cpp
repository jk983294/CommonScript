#include <atomic>
#include <cassert>
#include <thread>

/**
 * Sequential ordering may be necessary for multiple producer-multiple consumer situations
 * where all consumers must observe the actions of all producers occurring in the same order.
 *
 * Any other ordering in example may trigger the assert because it would be possible for
 * the threads c and d to observe changes to the atomics x and y in opposite order.
 */

std::atomic<bool> x = {false};
std::atomic<bool> y = {false};
std::atomic<int> z = {0};

void write_x() { x.store(true, std::memory_order_seq_cst); }

void write_y() { y.store(true, std::memory_order_seq_cst); }

void read_x_then_y() {
    while (!x.load(std::memory_order_seq_cst))
        ;
    if (y.load(std::memory_order_seq_cst)) {
        ++z;
    }
}

void read_y_then_x() {
    while (!y.load(std::memory_order_seq_cst))
        ;
    if (x.load(std::memory_order_seq_cst)) {
        ++z;
    }
}

int main() {
    std::thread a(write_x);
    std::thread b(write_y);
    std::thread c(read_x_then_y);
    std::thread d(read_y_then_x);
    a.join();
    b.join();
    c.join();
    d.join();
    assert(z.load() != 0);  // will never happen
}
