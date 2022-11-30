#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_key_t key;

void *threadfunc(void *parm) {
    void *value;
    int threadnum;
    int *tnum;
    char Buffer[128];

    tnum = static_cast<int *>(parm);
    threadnum = *tnum;

    printf("Thread %d executing\n", threadnum);

    if (!(value = malloc(sizeof(Buffer))))
        printf("Thread %d could not allocate storage, errno = %d\n", threadnum, errno);
    int status = pthread_setspecific(key, (void *)value);
    if (status < 0) {
        printf("pthread_setspecific failed, thread %d, errno %d", threadnum, errno);
        pthread_exit((void *)12);
    }
    printf("Thread %d setspecific value: %p\n", threadnum, value);

    auto pVoid = pthread_getspecific(key);
    if (status < 0) {
        printf("pthread_getspecific failed, thread %d, errno %d", threadnum, errno);
        pthread_exit((void *)13);
    }

    if (pVoid != value) {
        printf("getvalue not valid, getvalue=%p", pVoid);
        pthread_exit((void *)68);
    }

    pthread_exit((void *)0);
}

void destr_fn(void *parm) {
    printf("Destructor function invoked %p\n", parm);
    free(parm);
}

int main() {
    constexpr int threads = 3;
    int status;
    int i;
    int threadparm[threads];
    pthread_t threadid[threads];
    int thread_stat[threads];

    if ((status = pthread_key_create(&key, destr_fn)) < 0) {
        printf("pthread_key_create failed, errno=%d", errno);
        exit(1);
    }

    /* create 3 threads, pass each its number */
    for (i = 0; i < threads; i++) {
        threadparm[i] = i + 1;
        status = pthread_create(&threadid[i], NULL, threadfunc, (void *)&threadparm[i]);
        if (status < 0) {
            printf("pthread_create failed, errno=%d", errno);
            exit(2);
        }
    }

    for (i = 0; i < threads; i++) {
        status = pthread_join(threadid[i], (void **)&thread_stat[i]);
        if (status < 0) {
            printf("pthread_join failed, thread %d, errno=%d\n", i + 1, errno);
        }

        if (thread_stat[i] != 0) {
            printf("bad thread status, thread %d, status=%d\n", i + 1, thread_stat[i]);
        }
    }

    pthread_key_delete(key);
    return 0;
}