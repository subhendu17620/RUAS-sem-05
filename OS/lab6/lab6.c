#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_PHILOSOPHERS 5

void take_fork(int);
void put_fork(int);
void eat(int);

// binary semaphores
sem_t forks[MAX_PHILOSOPHERS];

/**
 * Function which drives the philosophers eating.
 * 
 * @param arg The int identifying the philosopher 
 */
void *act(void *arg)
{
    int philosopher = *(int *)arg;

    while (true)
    {
        printf("Philosopher %d is thinking\n", philosopher);

        // first take forks

        // this is key part to avoid deadlock. For one of the philosopher's
        // change the order of taking forks.
        if (philosopher == MAX_PHILOSOPHERS - 1)
        {
            // take right fork first
            take_fork((philosopher + 1) % MAX_PHILOSOPHERS);
            // take left fork
            take_fork(philosopher);
        }
        else
        {
            // take left fork first
            take_fork(philosopher);
            // take right fork
            take_fork((philosopher + 1) % MAX_PHILOSOPHERS);
        }

        // once forks are taken, eat
        eat(philosopher);
        sleep(2);

        // putdown forks
        put_fork(philosopher);
        put_fork((philosopher + 1) % MAX_PHILOSOPHERS);
    }
}

/**
 * Function that represents steps taken to obtain a resource, 
 * in this case, a fork.
 * 
 * @param fork The fork to take.
 */
void take_fork(int fork)
{
    sem_wait(&forks[fork]);
}

/**
 * Function that represents steps taken to release a resource,
 * in this case, a fork.
 * 
 * @param fork The fork to release.
 */
void put_fork(int fork)
{
    sem_post(&forks[fork]);
}

/**
 * Function that represents the steps taken once all the 
 * required resources (in this case, forks) are obtained.
 * For the dining philosopher problem, it is to eat.
 * 
 * @param philosopher The philosopher that obtained both 
 * the forks.
 */
void eat(int philosopher)
{
    printf("Philosopher %d is eating\n", philosopher);
}

int main()
{
    // creating threads
    pthread_t threads[MAX_PHILOSOPHERS];

    // initializing semaphores
    for (int i = 0; i < MAX_PHILOSOPHERS; i++)
        sem_init(&forks[i], 0, 1);

    // creating and spawning threads
    for (int i = 0; i < MAX_PHILOSOPHERS; i++)
        pthread_create(&threads[i], NULL, act, &i);

    // joining threads
    for (int i = 0; i < MAX_PHILOSOPHERS; i++)
        pthread_join(threads[i], NULL);
}
