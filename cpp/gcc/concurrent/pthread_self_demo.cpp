#include <pthread.h>
#include <stdio.h>
#include <cstdlib>

pthread_t thid, IPT;

void *thread(void *arg) {
    if (pthread_equal(IPT, pthread_self()))
        puts("the thread is the IPT...?");
    else
        puts("the thread is not the IPT");

    if (pthread_equal(thid, pthread_self()))
        puts("the thread is the one created by the IPT");
    else
        puts("the thread is not the one created by the IPT...?");

    pthread_exit((void *)0);
}

int main() {
    IPT = pthread_self();
    if (pthread_create(&thid, NULL, thread, NULL) != 0) {
        perror("pthread_create() error");
        exit(1);
    }

    if (pthread_join(thid, NULL) != 0) {
        perror("pthread_create() error");
        exit(3);
    }
}