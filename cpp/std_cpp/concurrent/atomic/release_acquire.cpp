#include <atomic>
#include <cassert>
#include <string>
#include <thread>
#include <vector>

/**
 * when the lock is released by thread A and acquired by thread B,
 * everything that took place in the critical section (before the release) in the context of thread A
 * has to be visible to thread B (after the acquire) which is executing the same critical section.
 */

std::atomic<std::string*> ptr;
int data;

void producer() {
    std::string* p = new std::string("Hello");
    data = 42;
    ptr.store(p, std::memory_order_release);  // release make above seen after consumer perform acquire successfully
}

void consumer() {
    std::string* p2;
    while (!(p2 = ptr.load(std::memory_order_acquire)))
        ;

    assert(*p2 == "Hello");  // never fires
    assert(data == 42);      // never fires
}

/**
 * transitive release-acquire ordering across three threads
 */
std::vector<int> v;
std::atomic<int> flag = {0};

void thread_1() {
    v.push_back(42);
    flag.store(1, std::memory_order_release);
}

void thread_2() {
    int expected = 1;
    while (!flag.compare_exchange_strong(expected, 2, std::memory_order_acq_rel)) {
        expected = 1;
    }
}

void thread_3() {
    while (flag.load(std::memory_order_acquire) < 2)
        ;
    assert(v.at(0) == 42);  // will never fire
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();

    // transitive release-acquire ordering across three threads
    std::thread a(thread_1);
    std::thread b(thread_2);
    std::thread c(thread_3);
    a.join();
    b.join();
    c.join();
}
