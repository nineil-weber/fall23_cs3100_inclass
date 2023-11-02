#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int count = 0;
pthread_mutex_t mutex;

void* incfn()
{
    for( int i =0; i < 100000000; i++)
    {
        pthread_mutex_lock(&mutex);
        count ++;
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t t1, t2;
    pthread_mutex_init(&mutex, NULL) ;

    printf("Process ID: %ld", getpid());

    pthread_create(&t1, NULL, incfn , NULL);
    pthread_create(&t2, NULL, incfn , NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);
    printf("\n Count value: %d\n", count);

    return 0;
}
