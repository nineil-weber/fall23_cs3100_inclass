#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>

//#include "common.h"
//#include "common_threads.h"

#ifdef linux
#include <semaphore.h>
#elif __APPLE__
#include "zemaphore.h"
#endif

int max;
int loops;
int *buffer;

int use  = 0;
int fill = 0;

sem_t empty;
sem_t full;
sem_t mutex;

#define CMAX (10)
int consumers = 1;

void print_buffer()
{
    int i;
    printf("[buffer = ");
    for(i=0; i<max;i++)
    {
        if (i == max-1)
            printf("%d", buffer[i]);
        else
            printf("%d, ", buffer[i]);
    }
    printf("]\n");
}

void do_fill(int value) {
    printf("[fill-start] fill: %d, max: %d, value: %d\n", fill, max, value);
    print_buffer();
    buffer[fill] = value;
    fill++;
    if (fill == max)
	    fill = 0;
    print_buffer();
    printf("[fill-end] fill: %d, max: %d\n", fill, max);
}

int do_get() {
    printf("[get-start] use: %d, max: %d\n", use, max);
    print_buffer();
    int tmp = buffer[use];
    use++;
    if (use == max)
	    use = 0;
    print_buffer();
    printf("[get-end] use: %d, max: %d, return_value: %d\n", use, max, tmp);
    return tmp;
}

void *producer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        Sem_wait(&empty);
        Sem_wait(&mutex);
        do_fill(i);
        Sem_post(&mutex);
        Sem_post(&full);
    }

    // end case
    for (i = 0; i < consumers; i++) {
        Sem_wait(&empty);
        Sem_wait(&mutex);
        do_fill(-1);
        Sem_post(&mutex);
        Sem_post(&full);
    }

    return NULL;
}
                                                                               
void *consumer(void *arg) {
    int tmp = 0;
    while (tmp != -1) {
        Sem_wait(&full);
        Sem_wait(&mutex);
        tmp = do_get();
        Sem_post(&mutex);
        Sem_post(&empty);
        printf("[consumer] id: %lld value: %d\n", (long long int) arg, tmp);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "usage: %s <buffersize> <loops> <consumers>\n", argv[0]);
        exit(1);
    }
    max   = atoi(argv[1]);
    loops = atoi(argv[2]);
    consumers = atoi(argv[3]);
    assert(consumers <= CMAX);

    buffer = (int *) malloc(max * sizeof(int));
    assert(buffer != NULL);
    int i;
    for (i = 0; i < max; i++) {
	    buffer[i] = 0;
    }

    Sem_init(&empty, max); // max are empty 
    Sem_init(&full, 0);    // 0 are full
    Sem_init(&mutex, 1);   // mutex

    pthread_t pid, cid[CMAX];
    pthread_create(&pid, NULL, producer, NULL);
    for (i = 0; i < consumers; i++) {
	    pthread_create(&cid[i], NULL, consumer, (void *) (long long int) i);
    }
    pthread_join(pid, NULL);
    for (i = 0; i < consumers; i++) {
	    pthread_join(cid[i], NULL);
    }
    return 0;
}

