#include <sys/time.h>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

uint64_t rdtsc() {
    unsigned int lo, hi;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}

double timeval2double(const timeval& ts) {
    return static_cast<double>(ts.tv_sec) + (static_cast<double>(ts.tv_usec) / 1000000.0);
}
double timespec2double(const timespec& ts) {
    return static_cast<double>(ts.tv_sec) + (static_cast<double>(ts.tv_nsec) / 1000000000.0);
}

int function2measure() {
    int sum = 0;
    for (int i = 0; i < 100000; ++i) {
        sum += i;
    }
    return sum;
}

int main(int argc, char* argv[]) {
    uint64_t cycle1 = rdtsc();
    int sum = function2measure();
    uint64_t cycle2 = rdtsc();
    cout << "sum is " << sum << " start at " << cycle1 << " end at " << cycle2 << " elapse: " << (cycle2 - cycle1)
         << endl;

    double t1, t2;
    timeval tv;
    gettimeofday(&tv, nullptr);
    t1 = timeval2double(tv);
    sum = function2measure();
    gettimeofday(&tv, nullptr);
    t2 = timeval2double(tv);
    cout << std::fixed << std::setprecision(9) << "sum is " << sum << " start at " << t1 << " end at " << t2
         << " elapse: " << (t2 - t1) << endl;

    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    t1 = timespec2double(ts);
    sum = function2measure();
    clock_gettime(CLOCK_REALTIME, &ts);
    t2 = timespec2double(ts);
    cout << std::fixed << std::setprecision(9) << "sum is " << sum << " start at " << t1 << " end at " << t2
         << " elapse: " << (t2 - t1) << endl;
    return 0;
}
