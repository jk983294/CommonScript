#include <atomic>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>

using namespace std;

std::atomic<int> shared_variable{0};

void reader_thread(size_t reader_name) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 * (rand() % 10)));

        // critical section
        int x = shared_variable.load(std::memory_order_acquire);
        cout << "reader " << reader_name << " " << x << endl;
        // critical section
    }
}

void writer_thread(size_t writer_name) {
    int x = 0;
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 * (rand() % 10)));

        // critical section
        x++;
        shared_variable.store(x, std::memory_order_release);
        cout << "writer " << writer_name << " " << x << endl;
        // critical section
    }
}

int main() {
    srand((unsigned)time(0));
    thread reader(reader_thread, 0);
    thread writer(writer_thread, 0);

    reader.join();
    writer.join();
    return 0;
}
