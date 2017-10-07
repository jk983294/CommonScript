#include <cstdlib>
#include <ctime>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int shared_variable = 0;
std::mutex mtx;

void reader_thread(size_t reader_name) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 * (rand() % 10)));

        lock_guard<mutex> guard(mtx);

        // critical section
        cout << "reader " << reader_name << " " << shared_variable << endl;
        // critical section
    }
}

void writer_thread(size_t writer_name) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 * (rand() % 10)));

        lock_guard<mutex> guard(mtx);

        // critical section
        ++shared_variable;
        cout << "writer " << writer_name << " " << shared_variable << endl;
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
