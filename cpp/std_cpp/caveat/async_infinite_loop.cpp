#include <chrono>
#include <future>
#include <iostream>
#include <string>
#include <thread>

using namespace std::chrono_literals;

void f() { std::this_thread::sleep_for(1s); }

int main() {
    auto fut = std::async(f);

    /**
     * default launch policy is std::launch::async | std::launch::deferred
     * std::launch::async launch policy means that f must be run asynchronously, i.e., on a different thread.
     * std::launch::deferred launch policy means that
     * f may run only when get or wait is called on the future returned by std::async.
     * f’s execution is deferred until such a call is made. If neither get nor wait is called, f will never run.
     *
     * if the launch policy chosen for f is std::launch::async, there’s no problem here
     * if std::launch::deferred chosen, it always return std::future_status::deferred, then infinite loop here
     */
    while (fut.wait_for(100ms) != std::future_status::ready) {
        std::cerr << "wait " << std::endl;
        std::this_thread::sleep_for(100ms);
    }
    return 0;
}
