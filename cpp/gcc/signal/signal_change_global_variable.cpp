#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t keep_going = 1;

static void catch_alarm(int sig) {
    keep_going = 0;
    signal(sig, catch_alarm);  // clears the flag and re-enables itself
}

void do_stuff(void) { puts("doing stuff while waiting for alarm...."); }

int main(void) {
    signal(SIGALRM, catch_alarm);

    alarm(3);  // arranges for a SIGALRM signal to be delivered to the calling process in seconds

    while (1) {
        if (keep_going) {
            do_stuff();
        } else {
            break;
        }
        sleep(1);
    }
    return 0;
}
