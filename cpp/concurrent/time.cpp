#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

using namespace std;

void function_call_time_measure(){
    /**
      * timing function call for performance tuning
      * steady_clock represents a monotonic clock, most suitable for measuring intervals
      */
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    cout << "Hello World" << endl;
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "took " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " ms." << endl;
}

int main() {
    std::chrono::seconds sec(1);
    // integer scale conversion with no precision loss: no cast
    cout << "1 second is: " << std::chrono::microseconds(sec).count() << " microseconds" << endl;
    // integer scale conversion with precision loss: requires a cast
    cout << std::chrono::duration_cast<std::chrono::minutes>(sec).count() << " minutes" << endl;

    std::chrono::time_point<std::chrono::system_clock> p1, p2, p3;
    p2 = std::chrono::system_clock::now();
    p3 = p2 - std::chrono::hours(24);

    std::time_t epoch_time = std::chrono::system_clock::to_time_t(p1);
    std::cout << "epoch: " << std::ctime(&epoch_time);
    std::time_t today_time = std::chrono::system_clock::to_time_t(p2);
    std::cout << "today: " << std::ctime(&today_time);

    std::cout << "hours since epoch: "
        << std::chrono::duration_cast<std::chrono::hours>(p2.time_since_epoch()).count() << endl;
    std::cout << "yesterday, hours since epoch: "
        << std::chrono::duration_cast<std::chrono::hours>(p3.time_since_epoch()).count() << endl;

    /**
     * system_clock represents the system-wide real time wall clock
     * the only clock that has the ability to map its time points to C-style time, and to be displayed.
     */
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
    cout << "24 hours ago, the time was " << std::put_time(std::localtime(&now_c), "%F %T") << endl; // g++5 fixed put_time

    function_call_time_measure();

    return 0;
}