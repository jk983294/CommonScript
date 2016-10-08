#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

void* a (void* p){
    for ( ; ;) {
        printf("inside a\n");
        sleep(1);
    }
}

// compile cmd: gcc thread.c -l pthread
int main() {
    pthread_t t_id;
    pthread_create(&t_id, NULL, a, NULL);
    for ( ; ;) {
        printf("inside main\n");
        sleep(1);
    }
    return 0;
}