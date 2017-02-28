#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 4

void* threadFunc(void *pArg)
{
    int myNum = *((int *)pArg);
    printf("Thread number %d\n", myNum);
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
    return 0;
}
