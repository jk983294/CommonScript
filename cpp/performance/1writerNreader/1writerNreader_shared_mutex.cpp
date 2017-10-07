#include <boost/thread/shared_mutex.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>

using namespace std;

/**
 * g++ 1writerNreader_shared_mutex.cpp -lboost_thread -lboost_system
 */

int shared_variable = 0;
boost::shared_mutex mtx;
bool something = true;

void reader_thread(size_t reader_name) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 * (rand() % 10)));

        boost::shared_lock<boost::shared_mutex> guard(mtx);

        // critical section
        cout << "reader " << reader_name << " " << shared_variable << endl;
        // critical section
    }
}

void writer_thread(size_t writer_name) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 * (rand() % 10)));

        boost::unique_lock<boost::shared_mutex> guard(mtx);

        // critical section
        ++shared_variable;
        cout << "writer " << writer_name << " " << shared_variable << endl;
        // critical section
    }
}

void conditional_writer_thread(size_t writer_name) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 * (rand() % 10)));

        boost::upgrade_lock<boost::shared_mutex> lock(mtx);  // read perm
        cout << "conditional reader " << writer_name << " " << shared_variable << endl;

        if (something) {
            boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);  // write perm
            ++shared_variable;
            cout << "conditional writer " << writer_name << " " << shared_variable << endl;
        }
    }
}

int main() {
    srand((unsigned)time(0));
    thread reader(reader_thread, 0);
    thread writer(writer_thread, 0);
    thread conditional_writer(conditional_writer_thread, 0);

    reader.join();
    writer.join();
    conditional_writer.join();
    return 0;
}
