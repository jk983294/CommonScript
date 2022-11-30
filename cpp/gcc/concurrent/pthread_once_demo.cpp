#include <cerrno>
#include <pthread.h>
#include <cstdio>
#include <cstdlib>

int once_counter = 0;
pthread_once_t once_control = PTHREAD_ONCE_INIT;

void once_fn() {
    puts("in once_fn");
    once_counter++;
}

void *threadfunc(void *parm) {
    int *tnum = static_cast<int *>(parm);
    int threadnum = *tnum;

    printf("Thread %d executing\n", threadnum);

    int status = pthread_once(&once_control, once_fn);
    if (status < 0) printf("pthread_once failed, thread %d, errno=%d\n", threadnum, errno);

    pthread_exit((void *)0);
}

int main() {
    constexpr int threads = 3;
    int threadparm[threads];
    pthread_t threadid[threads];
    int thread_stat[threads];

    for (int i = 0; i < threads; i++) {
        threadparm[i] = i + 1;
        int status = pthread_create(&threadid[i], NULL, threadfunc, (void *)&threadparm[i]);
        if (status < 0) {
            printf("pthread_create failed, errno=%d", errno);
            exit(2);
        }
    }

    for (int i = 0; i < threads; i++) {
        int status = pthread_join(threadid[i], (void **)&thread_stat[i]);
        if (status < 0) printf("pthread_join failed, thread %d, errno=%d\n", i + 1, errno);

        if (thread_stat[i] != 0) printf("bad thread status, thread %d, status=%d\n", i + 1, thread_stat[i]);
    }

    if (once_counter != 1) printf("once_fn did not get control once, counter=%d", once_counter);
    exit(0);
}