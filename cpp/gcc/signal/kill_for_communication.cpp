#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * a parent process forks a child process and then waits for the child to complete its initialization
 * The child process tells the parent when it is ready by sending it a SIGUSR1 signal, using the kill function
 */

volatile sig_atomic_t usr_interrupt = 0;

void synch_signal(int signo) { usr_interrupt = 1; }

void child_function(void) {
    // perform initialization.
    printf("child here! pid is %d.\n", (int)getpid());
    // let parent know you’re done.
    kill(getppid(), SIGUSR1);
    // Continue with execution
    printf("child leave...\n");
    exit(0);
}

int main(void) {
    struct sigaction usr_action;
    sigset_t block_mask;
    pid_t child_id;

    sigfillset(&block_mask);  // block all signals while in signal handler
    usr_action.sa_handler = synch_signal;
    usr_action.sa_mask = block_mask;
    usr_action.sa_flags = 0;
    sigaction(SIGUSR1, &usr_action, NULL);

    child_id = fork();
    if (child_id == 0) {
        child_function();  // does not return
    }

    // busy wait for the child to send a signal
    while (!usr_interrupt)
        ;

    // now continue execution
    printf("parent leave...\n");
    return 0;
}
