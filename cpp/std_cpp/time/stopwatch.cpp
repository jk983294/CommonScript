#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;
using namespace std::chrono;

int main() {
    /**
     * timing function call for performance tuning
     * steady_clock represents a monotonic clock, most suitable for measuring intervals
     */
    steady_clock::time_point start = steady_clock::now();
    cout << "Hello World" << endl;
    steady_clock::time_point end = steady_clock::now();
    cout << "took " << nanoseconds{end - start}.count() << " ns." << endl;
    return 0;
}
