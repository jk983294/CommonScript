#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>

using namespace std;

/**
 * promise provides a facility to store a value or an exception that is later acquired asynchronously
 * via a std::future object created by the std::promise object.
 * 1) create promise object
 * 2) get future object from promise object
 * 3) promise.set_value(something) to signal future
 */

void accumulate_data(std::vector<int>::iterator first, std::vector<int>::iterator last,
                     std::promise<int> accumulate_promise) {
    int sum = std::accumulate(first, last, 0);
    accumulate_promise.set_value(sum);              // notify future
}
void do_work(std::promise<void> barrier) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    barrier.set_value();                            // signal
}

int main() {
    /**
     * Demonstrate using promise<int> to transmit a result between threads.
     */
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
    std::promise<int> accumulate_promise;
    std::future<int> accumulate_future = accumulate_promise.get_future();
    std::thread work_thread(accumulate_data, numbers.begin(), numbers.end(), std::move(accumulate_promise));
    accumulate_future.wait();
    std::cout << "result=" << accumulate_future.get() << std::endl;
    work_thread.join();

    /**
     * Demonstrate using promise<void> to signal state between threads.
     */
    std::promise<void> barrier;
    std::future<void> barrier_future = barrier.get_future();
    std::thread new_work_thread(do_work, std::move(barrier));
    barrier_future.wait();                          // wait for signal from new_work_thread's barrier
    new_work_thread.join();
    return 0;
}