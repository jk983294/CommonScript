#include <iostream>
#include <thread>
#include "tbb/atomic.h"

using namespace tbb;
using namespace std;

// fetch_and_store fetch_and_add compare_and_swap

tbb::atomic<int> data;

void do_work() {
    data += 5;
    data -= 3;
    data++;
    data--;
    --data;
    ++data;

    data += 1;
    data -= 1;
}

int main() {
    tbb::atomic<int> ai(5);
    int expected = 5;
    bool exchanged = ai.compare_and_swap(expected, 3);
    std::cout << "ai= " << ai << "  exchanged= " << std::boolalpha << exchanged << std::endl;

    std::thread th1(do_work);
    std::thread th2(do_work);
    std::thread th3(do_work);
    std::thread th4(do_work);
    std::thread th5(do_work);

    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();

    std::cout << "result:" << data << std::endl;
    return 0;
}
