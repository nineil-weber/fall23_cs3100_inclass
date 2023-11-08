#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
//#include "common.h"
//#include "common_threads.h"

pthread_cond_t  c = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *child(void *arg) {
    printf("child: begin\n");
    pthread_mutex_lock(&m);
    printf("child: signal\n");
    pthread_cond_signal(&c);
    pthread_mutex_unlock(&m);
    return NULL;
}
int main(int argc, char *argv[]) {
    pthread_t p;
    printf("parent: begin\n");
    pthread_create(&p, NULL, child, NULL);
    sleep(2);
    printf("parent: wait to be signalled...\n");
    pthread_mutex_lock(&m);
    pthread_cond_wait(&c, &m);
    pthread_mutex_unlock(&m);
    printf("parent: end\n");
    return 0;
}

