#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <pthread.h>

#define N 10
sem_t bin_sem, full, empty;
int front = 0;
int rear = 0;
int CQueue[N];

int produce_item()
{
    int p = 1 + rand() % 300;
    return p;
}

void insert_item(int item)
{
    if (rear == N)
        rear = 0;
    CQueue[rear++] = item;
    printf("The Item Inserted is %d\n", item);
}

int remove_item()
{
    if (front == N)
        front = 0;
    int e = CQueue[front++];
    return e;
}

void consume_item(int item)
{
    printf("The Item Consumed is %d\n", item);
}

void *producer(void *a)
{
    int item, i;
    for (i = 0; i < N; i++)
    {
        item = produce_item();
        // decreasing empty semaphore; represents no: of empty slots
        // if the number of empty slots is 0 (i.e., the semaphore becomes
        // zero), the thread waits (for the consumer to consume an item).
        sem_wait(&empty);
        // locking bin_sem to gain exclusive access to critical region
        sem_wait(&bin_sem);
        // inserting item: critical region
        insert_item(item);
        // unlocking bin_sem to release access to critical region
        sem_post(&bin_sem);
        // increasing full semaphore; represents no: of full slots
        sem_post(&full);
    }
}

void *consumer(void *a)
{
    int item, i;
    for (i = 0; i < N; i++)
    {
        // decreasing full semaphore; represents no: of full slots
        // if the number of full slots is 0 (i.e., the semaphore becomes)
        // zero), the thread waits (for the producer to produce an item)
        sem_wait(&full);
        // locking bin_sem to gain exclusive access to critical region
        sem_wait(&bin_sem);
        // removing item: critical region
        item = remove_item();
        consume_item(item);
        // unlocking the bin_sem to release access to critical region
        sem_post(&bin_sem);
        // increasing empty semaphore; represents no: of empty slots
        sem_post(&empty);
    }
}

int main(int argc, char **argv)
{
    // initializing semaphores
    sem_init(&bin_sem, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, N);

    //initializing
    pthread_t th1, th2;
    int a;

    // creating threads
    pthread_create(&th1, NULL, producer, NULL);
    pthread_create(&th2, NULL, consumer, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    return (EXIT_SUCCESS);
}
