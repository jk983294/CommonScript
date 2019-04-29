#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * kill -USR2 pid
 *
 * sighandler_t signal (int signum, sighandler_t new_handler)
 * existing sighandler_t:
 * SIG_DFL default action
 * SIG_IGN the signal should be ignored
 * SIG_ERR If signal can't honor the request
 */

static void signal_handler(int signo) {
    if (signo == SIGUSR1)
        printf("caught SIGUSR1!\n");
    else if (signo == SIGUSR2)
        printf("caught SIGUSR2!\n");
    else {
        fprintf(stderr, "unexpected signal\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

int main(void) {
    if (signal(SIGUSR1, signal_handler) == SIG_ERR) {
        fprintf(stderr, "cannot handle SIGUSR1\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGUSR2, signal_handler) == SIG_ERR) {
        fprintf(stderr, "cannot handle SIGUSR2\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGPROF, SIG_DFL) == SIG_ERR) {  // default behaviour
        fprintf(stderr, "cannot reset SIGPROF\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGHUP, SIG_IGN) == SIG_ERR) {  // ignore this signal
        fprintf(stderr, "cannot ignore SIGHUP\n");
        exit(EXIT_FAILURE);
    }

    for (;;) pause();

    return 0;
}
