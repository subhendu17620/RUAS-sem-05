#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *sum(void *arg);
void *compare(void *arg);

int main(int argc, char const *argv[])
{
    int student1[] = {3, 4, 8, 7, 1};
    int student2[] = {9, 6, 9, 7, 8};

    int *sums = malloc(2 * sizeof(int));
    int result;
    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, sum, student1);
    pthread_create(&thread2, NULL, sum, student2);

    pthread_join(thread1, (void *)&sums[0]);
    pthread_join(thread2, (void *)&sums[1]);

    pthread_create(&thread3, NULL, compare, sums);
    pthread_join(thread3, (void *)&result);

    printf("the highest marks scored are: %d", result);

    return 0;
}

void *sum(void *arg)
{
    int *arr = (int *)arg;
    int res = 0;
    for (size_t i = 0; i < 5; i++)
    {
        res = res + arr[i];
    }
    return (void *)res;
}

void *compare(void *arg)
{
    int *totals = (int *)arg;
    if (totals[0] >= totals[1])
    {
        return (void *)totals[0];
    }
    return (void *)totals[1];
}

