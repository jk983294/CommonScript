#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * kill -USR2 pid
 *
 * sigaction allows you to specify additional flags to control when the signal is generated and how it is invoked
 *
 * option:
 * SA_NOCLDSTOP system delivers the signal for a terminated child process but not for one that is stopped
 * SA_ONSTACK system uses the signal stack when delivering that kind of signal
 * SA_RESTART If the flag is set, returning from a handler resumes the library function.
 *            If the flag is clear, returning from a handler makes the function fail with error code EINTR
 */

static void signal_handler(int signo) {
    if (signo == SIGUSR1)
        printf("caught SIGUSR1!\n");
    else if (signo == SIGUSR2)
        printf("caught SIGUSR2!\n");
    else {
        fprintf(stderr, "unexpected signal\n");
    }
}

int main(void) {
    struct sigaction sa_usr;
    struct sigaction old_action;
    sa_usr.sa_flags = 0;
    sa_usr.sa_handler = signal_handler;

    /**
     * old_action keeps previous handler, you can check if its handler is SIG_IGN
     * old_action.sa_handler != SIG_IGN
     */
    if (sigaction(SIGUSR1, &sa_usr, &old_action)) {
        fprintf(stderr, "cannot handle SIGUSR1\n");
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGUSR2, &sa_usr, NULL)) {
        fprintf(stderr, "cannot handle SIGUSR1\n");
        exit(EXIT_FAILURE);
    }

    struct sigaction temp;
    sigaction(SIGHUP, NULL, &temp);
    if (temp.sa_handler != SIG_IGN) {  // set new handler for SIGHUP only when it is not default behaviour
        temp.sa_handler = signal_handler;
        sigemptyset(&temp.sa_mask);
        sigaction(SIGHUP, &temp, NULL);
        fprintf(stderr, "set new handler for SIGHUP\n");
    }

    for (;;) {
        /**
         * causes the calling process (or thread) to sleep until a signal is delivered that
         * either terminates the process or causes the invocation of a signal-catching function
         */
        pause();
    }

    return 0;
}
