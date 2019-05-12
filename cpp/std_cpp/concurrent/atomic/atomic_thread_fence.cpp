#include <atomic>
#include <cassert>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

/**
 * fence-fence synchronization can be used to add synchronization to a sequence of several relaxed atomic operations
 */

const size_t count = 3;
std::atomic<int> status[count];
std::string data[count];  // non-atomic data

std::string computation(int v) { return std::to_string(v); }

void thread_a() {
    data[0] = computation(0);
    data[1] = computation(1);
    data[2] = computation(2);

    std::atomic_thread_fence(std::memory_order_release);

    std::atomic_store_explicit(&status[0], 0, std::memory_order_relaxed);
    std::atomic_store_explicit(&status[1], 1, std::memory_order_relaxed);
    std::atomic_store_explicit(&status[2], 2, std::memory_order_relaxed);
}

void thread_b() {
    int v0 = std::atomic_load_explicit(&status[0], std::memory_order_relaxed);
    int v1 = std::atomic_load_explicit(&status[1], std::memory_order_relaxed);
    int v2 = std::atomic_load_explicit(&status[2], std::memory_order_relaxed);

    std::atomic_thread_fence(std::memory_order_acquire);

    // v0, v1, v2 might turn out to be -1, some or all of them.
    // it is safe to read the non-atomic data because of the fences:
    if (v0 != -1) {
        cout << data[v0] << endl;
    }
    if (v1 != -1) {
        cout << data[v1] << endl;
    }
    if (v2 != -1) {
        cout << data[v2] << endl;
    }
}

/**
 * atomic-fence synchronization
 */

void thread_writer(int id) {
    // writer threads update non-atomic shared data and then update status[i]
    data[id] = computation(id);
    std::atomic_store_explicit(&status[id], id, std::memory_order_release);
}

void thread_reader(int my_id) {
    // Reader thread needs to check all mailbox[i], but only needs to sync with one
    for (size_t i = 0; i < count; ++i) {
        if (std::atomic_load_explicit(&status[i], std::memory_order_relaxed) == my_id) {
            std::atomic_thread_fence(std::memory_order_acquire);  // synchronize with just one writer
            // guaranteed to observe everything done in the writer thread before the atomic_store_explicit()
            cout << "reader " << data[i] << endl;
        }
    }
}

int main() {
    for (auto &i : status) {
        i = -1;
    }
    for (auto &str : data) {
        str = "";
    }
    std::thread t1(thread_a);
    std::thread t2(thread_b);
    t1.join();
    t2.join();

    for (auto &i : status) {
        i = -1;
    }
    for (auto &str : data) {
        str = "";
    }
    std::thread writer(thread_writer, 0);
    std::thread reader(thread_reader, 0);
    writer.join();
    reader.join();
}
