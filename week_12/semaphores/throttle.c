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
    Sem_wait(&s); 
    printf("child %lld\n", (long long int) arg);
    sleep(1);
    Sem_post(&s); 
    return NULL;
}

int main(int argc, char *argv[]) {
    /* Note: This code should work for Mac users.
     * For linux users, do the following changes:
     *  - Sem_wait --> sem_wait
     *  - Sem_post --> sem_post
     *  - Sem_init(&mutex, 1) --> sem_init(&mutex, 0, 1)
    */
    if (argc != 3) {
        fprintf(stderr, "usage: throttle <num_threads> <sem_value>\n");
        exit(1);
    }
    int num_threads = atoi(argv[1]);
    int sem_value = atoi(argv[2]);
    
    Sem_init(&s, sem_value); 

    printf("parent: begin\n");
    pthread_t c[num_threads];

    int i;
    for (i = 0; i < num_threads; i++) 
	    pthread_create(&c[i], NULL, child, (void *) (long long int)i);

    for (i = 0; i < num_threads; i++) 
	    pthread_join(c[i], NULL);

    printf("parent: end\n");
    return 0;
}
    
