#include <signal.h>
#include <stdio.h>

void handler(int sig);

void handler(int sig) {
    signal(sig, handler);
    printf("Receive signal: %d\n", sig);
}

int main(void) {
    signal(SIGHUP, handler);

    while (1) {
        sleep(1);
    }
    return 0;
}
