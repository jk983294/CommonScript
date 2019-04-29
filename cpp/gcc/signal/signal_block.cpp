#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void signal_handler(int signo) {
    if (signo == SIGUSR1)
        printf("caught SIGUSR1!\n");
    else if (signo == SIGUSR2)
        printf("caught SIGUSR2!\n");
    else {
        fprintf(stderr, "unexpected signal\n");
    }
    sleep(20);
    printf("handler finished");  // you can cancel during the sleep, it will ends after sleep
}

int main(void) {
    struct sigaction setup_action;
    sigset_t block_mask;
    sigemptyset(&block_mask);
    // block other terminal-generated signals while handler runs.
    sigaddset(&block_mask, SIGINT);
    sigaddset(&block_mask, SIGQUIT);
    setup_action.sa_handler = signal_handler;
    setup_action.sa_mask = block_mask;
    setup_action.sa_flags = 0;
    sigaction(SIGUSR1, &setup_action, NULL);
    sigaction(SIGUSR2, &setup_action, NULL);

    for (;;) pause();

    return 0;
}
