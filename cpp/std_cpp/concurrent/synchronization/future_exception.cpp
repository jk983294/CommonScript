#include <chrono>
#include <future>
#include <iostream>
#include <string>
#include <thread>

using namespace std;

void get_data(std::promise<int> data_promise) {
    try {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        throw(std::exception{});
        data_promise.set_value(42);
    } catch (...) {
        data_promise.set_exception(std::current_exception());
    }
}

int main() {
    std::promise<int> data_promise;
    std::future<int> data_future = data_promise.get_future();
    std::thread t(get_data, std::move(data_promise));
    try {
        cout << data_future.get() << endl;
    } catch (std::exception &e) {
        cout << e.what() << endl;
    }
    t.join();
    return 0;
}
