#include <atomic>
#include <cassert>
#include <string>
#include <thread>

/**
 * once the atomic load is completed, those operators and functions in thread B that
 * use the value obtained from the load are guaranteed to see what thread A wrote to memory.
 * the rest un-related variable may or may not be seen by other thread
 *
 * in the example, ptr is dependent variable, it guarantee to be seen by other thread
 * data is independent variable, no such guarantee
 */

std::atomic<std::string*> ptr;
int data;

void producer() {
    std::string* p = new std::string("Hello");
    data = 42;
    ptr.store(p, std::memory_order_release);
}

void consumer() {
    std::string* p2;
    while (!(p2 = ptr.load(std::memory_order_consume)))
        ;
    assert(*p2 == "Hello");  // never fires: *p2 carries dependency from ptr
    assert(data == 42);      // may or may not fire: data does not carry dependency from ptr
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}
