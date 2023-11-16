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

sem_t s;

void *child(void *arg) {
    sleep(2);
    printf("child\n");
    Sem_post(&s); // signal here: child is done
    return NULL;
}

int main(int argc, char *argv[]) {
    /* Note: This code should work for Mac users.
     * For linux users, do the following changes:
     *  - Sem_wait --> sem_wait
     *  - Sem_post --> sem_post
     *  - Sem_init(&mutex, 1) --> sem_init(&mutex, 0, 1)
    */
    Sem_init(&s, 0); 
    printf("parent: begin\n");
    pthread_t c;
    pthread_create(&c, NULL, child, NULL);
    Sem_wait(&s); // wait here for child
    printf("parent: end\n");
    return 0;
}
    
