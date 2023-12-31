#ifndef __zemaphore_h__
#define __zemaphore_h__
#include <pthread.h>

typedef struct __Zem_t {
    int value;
    pthread_cond_t  cond;
    pthread_mutex_t lock;
} Zem_t;

void Zem_init(Zem_t *z, int value) {
    z->value = value;
    pthread_cond_init(&z->cond, NULL);
    pthread_mutex_init(&z->lock, NULL);
}

void Zem_wait(Zem_t *z) {
    pthread_mutex_lock(&z->lock);
    while (z->value <= 0)
        pthread_cond_wait(&z->cond, &z->lock);
    z->value--;
    pthread_mutex_unlock(&z->lock);
}

void Zem_post(Zem_t *z) {
    pthread_mutex_lock(&z->lock);
    z->value++;
    pthread_cond_signal(&z->cond);
    pthread_mutex_unlock(&z->lock);
}

#ifdef __APPLE__
typedef Zem_t sem_t;

#define Sem_wait(s)    Zem_wait(s)
#define Sem_post(s)    Zem_post(s)
#define Sem_init(s, v) Zem_init(s, v)
#endif

#endif // __zemaphore_h__
