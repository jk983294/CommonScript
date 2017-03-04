#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* CONSTANTS =============================================================== */
#define NUM_READERS 5
#define NUM_READS 5
#define NUM_WRITERS 5
#define NUM_WRITES 5

/* GLOBAL SHARED DATA ====================================================== */
unsigned int gSharedValue = 0;
pthread_mutex_t gSharedMemoryLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t gReadPhase = PTHREAD_COND_INITIALIZER;
pthread_cond_t gWritePhase = PTHREAD_COND_INITIALIZER;
int gWaitingReaders = 0, gReaders = 0;

void *reader(void *threadArgument) {

	int id = *((int*)threadArgument);
	int i = 0, numReaders = 0;

	for(i = 0; i < NUM_READS; i++) {
		// Wait so that reads and writes do not all happen at once
	  usleep(1000 * (random() % NUM_READERS + NUM_WRITERS));

		// Enter critical section
	  pthread_mutex_lock(&gSharedMemoryLock);
	  	gWaitingReaders++;
	  	while (gReaders == -1) {
	  		pthread_cond_wait(&gReadPhase, &gSharedMemoryLock);
	  	}
	  	gWaitingReaders--;
	  	numReaders = ++gReaders;
	  pthread_mutex_unlock(&gSharedMemoryLock);

	  // Read data
	  fprintf(stdout, "[r%d] reading %u  [readers: %2d]\n", id, gSharedValue, numReaders);

	  // Exit critical section
	  pthread_mutex_lock(&gSharedMemoryLock);
	  	gReaders--;
	  	if (gReaders == 0) {
	  		pthread_cond_signal(&gWritePhase);
	  	}
	  pthread_mutex_unlock(&gSharedMemoryLock);
	}

	pthread_exit(0);
}

void *writer(void *threadArgument) {

	int id = *((int*)threadArgument);
	int i = 0, numReaders = 0;

	for(i = 0; i < NUM_WRITES; i++) {
	  // Wait so that reads and writes do not all happen at once
	  usleep(1000 * (random() % NUM_READERS + NUM_WRITERS));

		// Enter critical section
	  pthread_mutex_lock(&gSharedMemoryLock);
	  	while (gReaders != 0) {
	  		pthread_cond_wait(&gWritePhase, &gSharedMemoryLock);
	  	}
	  	gReaders = -1;
	  	numReaders = gReaders;
	  pthread_mutex_unlock(&gSharedMemoryLock);

	  // Write data
	  fprintf(stdout, "[w%d] writing %u* [readers: %2d]\n", id, ++gSharedValue, numReaders);

	  // Exit critical section
	  pthread_mutex_lock(&gSharedMemoryLock);
	  	gReaders = 0;
	  	if (gWaitingReaders > 0) {
	  		pthread_cond_broadcast(&gReadPhase);
	  	}
	  	else {
	  		pthread_cond_signal(&gWritePhase);
	  	}
	  pthread_mutex_unlock(&gSharedMemoryLock);
  }

  pthread_exit(0);
}

int main(int argc, char **argv) {
	int i;
	int readerNum[NUM_READERS];
	int writerNum[NUM_WRITERS];

	pthread_t readerThreadIDs[NUM_READERS];
	pthread_t writerThreadIDs[NUM_WRITERS];

	srandom((unsigned int)time(NULL));

	for(i = 0; i < NUM_READERS; i++) {
		readerNum[i] = i;
		pthread_create(&readerThreadIDs[i], NULL, reader, &readerNum[i]);
	}

	for(i = 0; i < NUM_WRITERS; i++) {
		writerNum[i] = i;
		pthread_create(&writerThreadIDs[i], NULL, writer, &writerNum[i]);
	}

	for(i = 0; i < NUM_READERS; i++) {
		pthread_join(readerThreadIDs[i], NULL);
	}

	for(i = 0; i < NUM_WRITERS; i++) {
		pthread_join(writerThreadIDs[i], NULL);
	}

  return 0;
}
