#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

using namespace std;

int main() {
    std::chrono::seconds sec(1);
    // integer scale conversion with no precision loss: no cast
    cout << "1 second is: " << std::chrono::microseconds(sec).count() << " microseconds" << endl;
    // integer scale conversion with precision loss: requires a cast
    cout << std::chrono::duration_cast<std::chrono::minutes>(sec).count() << " minutes" << endl;

    /**
     * system_clock represents the system-wide real time wall clock
     * the only clock that has the ability to map its time points to C-style time, and to be displayed.
     */
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
    cout << "24 hours ago, the time was " << std::put_time(std::localtime(&now_c), "%F %T") << endl; // g++5 fixed put_time

    /**
     * timing function call for performance tuning
     * steady_clock represents a monotonic clock, most suitable for measuring intervals
     */
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    cout << "Hello World" << endl;
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "took " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " ms." << endl;

    return 0;
}