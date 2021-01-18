#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define MaxItems 2    // Maximum items a producer can produce or a consumer can consume
#define SpoolerSize 5 // Size of the buffer

sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int spooler[SpoolerSize];
pthread_mutex_t mutex;

void *producer(void *pno)
{
    int item;
    for (int i = 0; i < MaxItems; i++)
    {
        item = rand(); // Produce an random item
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        spooler[in] = item;
        printf("Process %d: Insert document %d at index %d\n", *((int *)pno), spooler[in], in);
        in = (in + 1) % SpoolerSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}
void *consumer(void *cno)
{
    for (int i = 0; i < MaxItems; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = spooler[out];
        printf("PRINTER : Prints document %d from index %d\n", item, out);
        out = (out + 1) % SpoolerSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main()
{

    pthread_t pro[5], con;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, SpoolerSize);
    sem_init(&full, 0, 0);

    int a[5] = {1, 2, 3, 4, 5}; //Just used for numbering the producer and consumer

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&con, NULL, (void *)consumer, (void *)&a[i]);
        pthread_join(con, NULL);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(pro[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}