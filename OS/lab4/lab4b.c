#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3

void *callbackFunc(void *);

int main()
{
    int ret_code;
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
    {
        ret_code = pthread_create(&threads[i], NULL, callbackFunc, NULL);
        if (ret_code)
        {
            printf("Error creating thread. error code: %d", ret_code);
            exit(-1);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);
}

void *callbackFunc(void *args)
{
    printf("Hello World! id: %ld\n", pthread_self());
}

