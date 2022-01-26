#include <atomic>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

struct Object {
    void init() {  // make sure this init exactly once
        auto calc_init = [&]() {
            m_val = 42;
            cout << "init\n";
        };
        std::call_once(m_init_called, calc_init);
    }

    void work(int id) {
        init();

        while (true) {
            int64_t new_val = m_val.fetch_add(1);
            printf("worker %d val=%ld\n", id, new_val);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 * (rand() % 5)));
        }
    }
    std::atomic<int64_t> m_val;
    std::once_flag m_init_called;
};

void worker(Object& o, int id) { o.work(id); }

int main() {
    Object o;
    std::vector<thread> consumers;

    for (int i = 0; i < 5; i++) {
        std::thread consumer(std::bind(&worker, std::ref(o), i + 1));
        consumers.push_back(std::move(consumer));
    }

    for (auto& consumer : consumers) {
        consumer.join();
    }
}