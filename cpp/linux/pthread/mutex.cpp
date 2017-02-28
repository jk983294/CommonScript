#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 4

pthread_mutex_t count_mutex;
int count;

void increment_count()
{
    pthread_mutex_lock(&count_mutex);
    ++count;
    pthread_mutex_unlock(&count_mutex);
}

void* threadFunc(void *pArg)
{
    int myNum = *((int *)pArg);
    printf("Thread number %d\n", myNum);

    for (int i = 0; i < 100; i++)
    {
        increment_count();
    }
    return 0;
}

int main()
{
    pthread_t tid[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
    {
        int local = i;
        pthread_create(&tid[i], NULL, threadFunc, &local);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(tid[i], NULL);
    }

    printf("final count %d\n", count);
    return 0;
}
