#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
//#include "common.h"
//#include "common_threads.h"

//
// Simple sync "object"
//

typedef struct {
    pthread_cond_t c;
    pthread_mutex_t m;
    int done;
} synchronizer_t;

synchronizer_t s;

void sync_init(synchronizer_t *s) {
    s->done = 0;
//    s->m = PTHREAD_MUTEX_INITIALIZER;
//    s->c = PTHREAD_COND_INITIALIZER;
    pthread_mutex_init(&s->m, NULL);
    pthread_cond_init(&s->c, NULL);
}

void sync_signal(synchronizer_t *s) {
    pthread_mutex_lock(&s->m);
    s->done = 1;
    pthread_cond_signal(&s->c);
    pthread_mutex_unlock(&s->m);
}

void sync_wait(synchronizer_t *s) {
    pthread_mutex_lock(&s->m);
    while (s->done == 0)
        pthread_cond_wait(&s->c, &s->m);
    s->done = 0; // reset for next use
    pthread_mutex_unlock(&s->m);
}


//
// Main threads
//

void *child(void *arg) {
    printf("child\n");
    sleep(1);
    sync_signal(&s);
    return NULL;
}
int main(int argc, char *argv[]) {
    pthread_t p;
    printf("parent: begin\n");
    sync_init(&s);
    pthread_create(&p, NULL, child, NULL);
    sync_wait(&s);
    printf("parent: end\n");
    return 0;
}

