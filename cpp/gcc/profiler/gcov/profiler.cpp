#include <iostream>

using namespace std;

/**
 * g++ -fprofile-arcs -ftest-coverage profiler.cpp
 *
 * gcov profiler.cpp
 * vim profiler.cpp.gcov
 *
 * gcov -b profiler.cpp
 * vim profiler.cpp.gcov
 */

int calc(int x) {
    if (x % 7 == 0) {
        return x + 1;
    } else if (x % 7 == 1) {
        return x * 2;
    } else {
        return x / 2;
    }
}

int main() {
    int sum = 0;
    for (int i = 0; i < 100; ++i) {
        sum += calc(i);
    }
    cout << sum << endl;
    return 0;
}
