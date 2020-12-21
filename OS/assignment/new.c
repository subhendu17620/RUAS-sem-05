#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define CORE 12

// struct arg_struct
// {
//     int arg1;
//     int arg2;
// };
int step = 0;

void *parallel_addition(void *arg)
{

    int core = (int)step;

    // Each thread computes 1/4th of matrix addition
    for (size_t i = core * MAX / CORE; i < (core + 1) * MAX / CORE; i++)
    {

        for (size_t j = 0; j < MAX; j++)
        {
            // Compute Sum Row wise
            arr[2][i][j] = mat_A[i][j] + mat_B[i][j];
        }
    }
}

int main(int argc, char **argv)
{
    printf("%lld", atoll(argv[1]));
    int MAX = atoll(argv[1]);

    int mat_A[MAX][MAX], mat_B[MAX][MAX], sum[MAX][MAX];

    for (size_t i = 0; i < MAX; i++)
    {

        for (size_t j = 0; j < MAX; j++)
        {
            mat_A[i][j] = rand() % 10;
            mat_B[i][j] = rand() % 10;
        }
    }

    pthread_t thread[CORE];

    int arr[3][MAX][];
    arr[0] = mat_A;
    arr[1] = mat_B;
    arr[2] = sum;

    for (size_t i = 0; i < CORE; i++)
    {
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&thread[i], &attr, parallel_addition, NULL);
        step++;
    }

    for (size_t i = 0; i < CORE; i++)
    {
        // Waiting for join threads after compute
        pthread_join(thread[i], NULL);
    }
}