#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

/**
* reader blocks writer, don't block reader
* writer blocks writer and reader
*/
#define NUM_READERS 5
#define NUM_WRITERS 5

int shared_variable = 0;
int read_count = 0;
int write_count = 0;
std::mutex rw_mtx;
std::condition_variable rw_write_q;
std::condition_variable rw_read_q;

void reader_thread(size_t reader_name)
{
    while (true) {
        std::unique_lock<std::mutex> rw_lock(rw_mtx);
        rw_read_q.wait(rw_lock, []{ return write_count == 0; });    // wait for no writer
        read_count += 1;                                            // announce intention to read
        rw_lock.unlock();

        // critical section
        cout << "reader " << reader_name << " " << shared_variable << endl;
        // critical section

        rw_lock.lock();
        read_count -= 1;                                            // announce no intention to read
        if (read_count == 0)
        {
            rw_write_q.notify_one();
        }
        rw_lock.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 * (rand() % NUM_READERS + NUM_WRITERS)));
    }
}

void writer_thread(size_t writer_name)
{
    while (true) {
        std::unique_lock<std::mutex> rw_lock(rw_mtx);
        rw_write_q.wait(rw_lock,
            []{ return read_count == 0 && write_count == 0; });     // wait for no reader and no writer
        write_count = 1;                                            // announce intention to write
        rw_lock.unlock();

        // critical section
        ++shared_variable;
        cout << "writer " << writer_name << " " << shared_variable << endl;
        // critical section

        rw_lock.lock();
        write_count = 0;
        if (write_count > 0)
        {
            rw_read_q.notify_all();                                 // notify all readers
            rw_write_q.notify_one();                                // notify one writer
        }
        rw_lock.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 * (rand() % NUM_READERS + NUM_WRITERS)));
    }
}

int main(){
    srand((unsigned)time(0));
    vector<thread> readers, writers;
    for (size_t i = 0; i < NUM_READERS; i++)
    {
        readers.push_back(thread(reader_thread, i));
    }

    for (size_t i = 0; i < NUM_WRITERS; i++)
    {
        writers.push_back(thread(writer_thread, i));
    }

    for (auto i = readers.begin(); i < readers.end(); i++)
    {
        (*i).join();
    }

    for (auto i = writers.begin(); i < writers.end(); i++)
    {
        (*i).join();
    }
    return 0;
}
