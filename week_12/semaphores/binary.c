#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//#include "common.h"
//#include "common_threads.h"

#ifdef linux
#include <semaphore.h>
#elif __APPLE__
#include "zemaphore.h"
#endif

sem_t mutex;
volatile int counter = 0;

void *child(void *arg) {
    int i;
    for (i = 0; i < 10000000; i++) {
        Sem_wait(&mutex);
        counter++;
        Sem_post(&mutex);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    /* Note: This code should work for Mac users.
     * For linux users, do the following changes:
     *  - Sem_wait --> sem_wait
     *  - Sem_post --> sem_post
     *  - Sem_init(&mutex, 1) --> sem_init(&mutex, 0, 1)
    */
    Sem_init(&mutex, 1);
    pthread_t c1, c2;
    pthread_create(&c1, NULL, child, NULL);
    pthread_create(&c2, NULL, child, NULL);
    pthread_join(c1, NULL);
    pthread_join(c2, NULL);
    printf("result: %d (should be 20000000)\n", counter);
    return 0;
}
    
