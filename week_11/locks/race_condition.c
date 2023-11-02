#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int count = 0;

void* incfn()
{
    for( int i =0; i < 100000000; i++)
    {
        count ++;
    }
}

int main()
{
    pthread_t t1, t2;

    printf("Process ID: %ld", getpid());

    pthread_create(&t1, NULL, incfn , NULL);
    pthread_create(&t2, NULL, incfn , NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("\n Count value: %d\n", count);

    return 0;
}
