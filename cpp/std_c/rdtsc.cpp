#include <iostream>
#include <string>

using namespace std;

uint64_t rdtsc() {
    unsigned int lo, hi;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}

int main(int argc, char *argv[]) {
    uint64_t cycle1 = rdtsc();
    int sum = 0;
    for (int i = 0; i < 10; ++i) {
        sum += i;
        uint64_t cycle2 = rdtsc();
        cout << cycle1 << " " << cycle2 << " " << (cycle2 - cycle1) << endl;
        cycle1 = cycle2;
    }
    cout << "test end..." << endl;
    return 0;
}
