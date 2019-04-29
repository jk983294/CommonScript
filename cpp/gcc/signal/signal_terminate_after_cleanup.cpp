#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t fatal_error_in_progress = 1;

static void fatal_error_signal(int sig) {
    /**
     * since this handler is established for more than once, cleabup already, then we exit
     */
    if (fatal_error_in_progress) {
        raise(sig);
    }

    fprintf(stderr, "handle error\n");
    fatal_error_in_progress = 1;

    /**
     * Now do the clean up actions:
     * - reset terminal modes
     * - kill child processes
     * - remove lock files
     */

    /**
     * reactivate the signal's default handling, which is to terminate the process.
     * we could just call exit or abort, but reraising the signal sets the return status from the process correctly.
     * so we re-trigger this signal
     */
    signal(sig, SIG_DFL);
    raise(sig);
}

int main(void) {
    signal(SIGINT, fatal_error_signal);

    while (1) {
        pause();
    }
    return 0;
}
