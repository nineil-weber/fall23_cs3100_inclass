#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
//#include "common.h"
//#include "common_threads.h"

pthread_cond_t  c = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int done = 0;

void *child(void *arg) {
    printf("child: begin\n");
    sleep(1);
    done = 1;
    printf("child: signal\n");
    pthread_cond_signal(&c);
    return NULL;
}
int main(int argc, char *argv[]) {
    pthread_t p;
    printf("parent: begin\n");
    pthread_create(&p, NULL, child, NULL);
    pthread_mutex_lock(&m);
    printf("parent: check condition\n");
    while (done == 0) {
	    sleep(2);
        printf("parent: wait to be signalled...\n");
        pthread_cond_wait(&c, &m);
    }
    pthread_mutex_unlock(&m);
    printf("parent: end\n");
    return 0;
}