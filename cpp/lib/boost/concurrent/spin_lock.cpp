#include <future>
#include <iostream>
#include "boost/smart_ptr/detail/spinlock.hpp"

// g++ -std=c++11 -O3 -o spin_lock spin_lock.cpp && time ./spin_lock

boost::detail::spinlock lock;
volatile int value = 0;

int loop(bool inc, int limit) {
    std::cout << "Started " << inc << " " << limit << std::endl;
    for (int i = 0; i < limit; ++i) {
        std::lock_guard<boost::detail::spinlock> guard(lock);
        if (inc) {
            ++value;
        } else {
            --value;
        }
    }
    return 0;
}

int main() {
    auto f = std::async(std::launch::async, std::bind(loop, true, 20000000));
    loop(false, 10000000);
    f.wait();
    std::cout << value << std::endl;
}
