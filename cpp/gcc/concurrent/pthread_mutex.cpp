#include <pthread.h>
#include <stdio.h>
#include <cstdlib>

pthread_mutex_t mutex;

void *thread_proc(void *arg) {
    if (pthread_mutex_lock(&mutex) != 0) {
        perror("pthread_mutex_lock() error");
        exit(1);
    }

    puts("thread was granted the mutex");

    if (pthread_mutex_unlock(&mutex) != 0) {
        perror("pthread_mutex_unlock() error");
        exit(2);
    }
    pthread_exit((void *)0);
}

int main() {
    pthread_t thid;

    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("pthread_mutex_init() error");
        exit(3);
    }

    if (pthread_create(&thid, NULL, thread_proc, NULL) != 0) {
        perror("pthread_create() error");
        exit(4);
    }
    if (pthread_mutex_lock(&mutex) != 0) {
        perror("pthread_mutex_lock() error");
        exit(5);
    }

    puts("IPT was granted the mutex");

    if (pthread_mutex_unlock(&mutex) != 0) {
        perror("pthread_mutex_unlock() error");
        exit(6);
    }

    if (pthread_join(thid, NULL) != 0) {
        perror("pthread_mutex_lock() error");
        exit(7);
    }
}