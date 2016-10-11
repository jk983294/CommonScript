#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>

using namespace std;

/**
 * producer consumer
 */

struct DataChunk {};
DataChunk produce_data() {
    cout << "producer" << endl;
    return DataChunk();
}
void consume_data(DataChunk &) {
    cout << "consumer" << endl;
}

std::mutex mut;
std::queue<DataChunk> data_queue;
std::condition_variable data_cond;

void producer_thread()
{
    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        DataChunk const data = produce_data();
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
}

void consumer_thread()
{
    while(true) {
        std::unique_lock<std::mutex> lk(mut);
        // check once, if failed, unlock lk and block this thread util notified
        // when notified, first acquire lock, then check condition
        data_cond.wait(lk, []{return !data_queue.empty();});
        DataChunk data = data_queue.front();
        data_queue.pop();
        lk.unlock();
        consume_data(data);
    }
}

int main(){
    std::thread t1(producer_thread);
    std::thread t2(consumer_thread);
    t1.join();
    t2.join();
    return 0;
}