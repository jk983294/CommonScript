#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * producer consumer
 */

#define BUF_SIZE 3                                              // size of shared buffer

int buffer[BUF_SIZE];                                           // shared buffer
int add_pos = 0;                                                // next add position
int remove_pos = 0;                                             // next remove position
int data_count = 0;                                             // total data count

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;                  // mutex for buffer
pthread_cond_t c_consumer = PTHREAD_COND_INITIALIZER;           // consumer waits on this condition variable
pthread_cond_t c_producer = PTHREAD_COND_INITIALIZER;           // producer waits on this condition variable

void* producer_thread(void *param)
{
    int next_data = 0;
    while(true) {
        sleep(2);

        pthread_mutex_lock(&m);
        if(data_count == BUF_SIZE) {                            // buffer is full, wait for consumer's signal
            pthread_cond_wait(&c_producer, &m);
        }
        buffer[add_pos] = next_data;
        add_pos = (add_pos + 1) % BUF_SIZE;
        ++data_count;
        pthread_mutex_unlock(&m);

        pthread_cond_signal(&c_consumer);                       // signal consumer to consume

        printf("producer: insert %d\n", next_data);
        fflush(stdout);
        ++next_data;
    }
    return 0;
}

void* consumer_thread(void *param)
{
    int data;
    while(true) {
        pthread_mutex_lock(&m);
        if(data_count == 0) {                                   // buffer is empty, wait for producer's signal
            pthread_cond_wait(&c_consumer, &m);
        }
        data = buffer[remove_pos];
        remove_pos = (remove_pos + 1) % BUF_SIZE;
        --data_count;
        pthread_mutex_unlock(&m);

        pthread_cond_signal(&c_producer);                       // signal producer to produce

        printf("consumer: value %d\n", data);
        fflush(stdout);
    }
    return 0;
}

int main(){
    pthread_t producer, consumer;
    pthread_create(&producer, NULL, producer_thread, NULL);
    pthread_create(&consumer, NULL, consumer_thread, NULL);
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);
    return 0;
}
