#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>  //sleep func here

void* F1(void * args)
{
    while(1)
    {
        printf("F1------\n");
        sleep(1);
    }
}
void* F2(void* args)
{
    while(1)
    {
        printf("F2------\n");
        sleep(1);
    }
}


int main()
{
    pthread_t t1, t2;

    int rc1;
    int rc2;

    rc1 = pthread_create(&t1, NULL, F1, NULL);
    rc2 = pthread_create(&t2, NULL, F2, NULL);


    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
