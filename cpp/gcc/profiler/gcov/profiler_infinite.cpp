#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace std;

extern "C" void __gcov_flush();

/**
 * g++ -fprofile-arcs -ftest-coverage profiler_infinite.cpp
 * ./a.out &
 * kill -USR1 96783
 *
 * gcov profiler_infinite.cpp
 * vim profiler_infinite.cpp.gcov
 *
 * gcov -b profiler_infinite.cpp
 * vim profiler_infinite.cpp.gcov
 */

void sigterm_handler(int signum) {
    cout << "received signal" << endl;
    __gcov_flush();  // dump coverage data on receiving SIGUSR1
    exit(1);
}

void reg_sigterm_handler(void (*handler)(int s)) {
    struct sigaction action, old_action;

    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    sigaction(SIGUSR1, NULL, &old_action);
    if (old_action.sa_handler != SIG_IGN) {
        sigaction(SIGUSR1, &action, NULL);
    }
}

int calc(int x) {
    if (x % 7 == 0) {
        return x + 1;
    } else if (x % 7 == 1) {
        return x - 5;
    } else {
        return x / 2 + 1;
    }
}

int main() {
    reg_sigterm_handler(sigterm_handler);

    int sum = 0, index = 0;
    while (true) {
        sum = calc(index++);
        usleep(1000);
    }
}
