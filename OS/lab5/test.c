#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/unistd.h>
#define N 10

// defining mutexes
pthread_mutex_t mutex;
pthread_cond_t condc, condp;

// defining queue vars
int front = 0;
int rear = 0;
int CQueue[N];

int current_buffer_size = 0;
int p, sum = 0;

int produce_item()
{
    srand(time(NULL));
    p = 1 + rand() % 40;
    return p;
}

void insert_item(int item)
{
    if (rear == N)
        rear = 0;
    CQueue[rear++] = item;
    current_buffer_size++;
    printf("The Item Inserted is %d\n", item);
}
int remove_item()
{
    if (front == N)
        front = 0;
    int e = CQueue[front++];
    current_buffer_size--;
    printf("%d was removed !\n", p);
    return e;
}
void consume_item(int item)
{
    sum += item;
    printf("The Item %d is Consumed\n\n", item);
}
void *producer(void *a)
{
    int i, item;
    for (i = 0; i < N; i++)
    {
        // locks the critical region
        pthread_mutex_lock(&mutex);

        item = produce_item();

        // if buffer is full, wait and unlock mutex
        // while loop used to avoid spurious wakeups
        while (current_buffer_size == N)
            pthread_cond_wait(&condp, &mutex);

        // insert item
        insert_item(item);
        // wake up consumer
        pthread_cond_signal(&condc);
        // unlock critical region
        pthread_mutex_unlock(&mutex);
    }
}
void *consumer(void *a)
{
    int i, item;
    for (i = 0; i < N; i++)
    {
        // locks the cirtical region
        pthread_mutex_lock(&mutex);
        // if buffer is empty
        // while loop used to avoid spurious wakeups
        while (current_buffer_size == 0)
            pthread_cond_wait(&condc, &mutex);
        // remove item
        item = remove_item();
        // clear buffer
        current_buffer_size = 0;
        // consume item
        consume_item(item);
        // wake up producer if sleeping
        pthread_cond_signal(&condp);
        // unlock critical region
        pthread_mutex_unlock(&mutex);
    }
}
int main(int argc, char **argv)
{
    // creating muxtes
    pthread_mutex_init(&mutex, 0);
    pthread_cond_init(&condp, 0);
    pthread_cond_init(&condc, 0);
    // creating threads
    pthread_t th1, th2;
    int a;
    // spawing threads
    pthread_create(&th1, NULL, producer, NULL);
    pthread_create(&th2, NULL, consumer, NULL);
    // joining threads
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    // destroying mutexes
    pthread_cond_destroy(&condc);
    pthread_cond_destroy(&condp);
    pthread_mutex_destroy(&mutex);
}
