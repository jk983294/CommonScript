#include <thread>
#include <future>
#include <iostream>
#include <chrono>

/**
 * future_status, waits for the result to become available.
 * Blocks until specified timeout_duration has elapsed or the result becomes available,
 * whichever comes first. returns value identifies the state of the result.
 */

int main() {
    std::future<int> future = std::async(std::launch::async, [](){
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return 8;
    });

    std::cout << "waiting..." << std::endl;
    std::future_status status;
    do {
        status = future.wait_for(std::chrono::seconds(1));
        if (status == std::future_status::deferred) {
            std::cout << "deferred" << std::endl;
        } else if (status == std::future_status::timeout) {
            std::cout << "timeout" << std::endl;
        } else if (status == std::future_status::ready) {
            std::cout << "ready!" << std::endl;
        }
    } while (status != std::future_status::ready);

    std::cout << "result is " << future.get() << std::endl;
    return 0;
}