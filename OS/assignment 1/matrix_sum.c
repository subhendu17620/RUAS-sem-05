#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/sysinfo.h>

// function prototypes
void *parallel_addition(void *arg);
void *sequential_addition(void *arg);
void generateMatrix();
void sequential_approach();
void parallel_approach();

// Value depend on System core
#define CORE 12

// Maximum matrix size
#define MAX 15000

// initializing matrix
int mat_A[MAX][MAX], mat_B[MAX][MAX], sum[MAX][MAX];

// Driver Code
int main(int argc, char *argv[])
{
    // chexking how many cores available
    // printf("This system has %d processors configured and "
    //        "%d processors available.\n",
    //        get_nprocs_conf(), get_nprocs());

    //genearating matrix A and matrix B with random values
    generateMatrix();
    // Displaying mat_A
    // printf("\nMatrix A:\n");

    // for (size_t i = 0; i < MAX; i++)
    // {
    //     for (size_t j = 0; j < MAX; j++)
    //     {

    //         printf("%d ", mat_A[i][j]);
    //     }

    //     printf("\n");
    // }

    // Displaying mat_B
    // printf("\nMatrix B:\n");

    // for (size_t i = 0; i < MAX; i++)
    // {
    //     for (size_t j = 0; j < MAX; j++)
    //     {

    //         printf("%d ", mat_B[i][j]);
    //     }

    //     printf("\n");
    // }

    if (strcmp(argv[1], "--sequential") == 0)
    {
        printf("Running in sequential mode.\n");
        sequential_approach();
    }
    else
    {
        printf("Running in parallel mode.\n");
        parallel_approach();
    }

    return 0;
}

// Addition of a Matrix
void *parallel_addition(void *arg)
{

    int core = (int)arg;

    // Each thread computes 1/CORE th of matrix addition
    for (size_t i = core * MAX / CORE; i < (core + 1) * MAX / CORE; i++)
    {
        for (size_t j = 0; j < MAX; j++)
        {
            // Compute Sum Row wise
            sum[i][j] = mat_A[i][j] + mat_B[i][j];
        }
    }
    // pthread_exit(NULL);
}
void *sequential_addition(void *arg)
{
    for (int _ = 0; _ < 3; _++)
        for (size_t i = 0; i < MAX; i++)
        {
            for (size_t j = 0; j < MAX; j++)
            {
                // Compute Sum Row wise
                sum[i][j] = mat_A[i][j] + mat_B[i][j];
            }
        }
    // pthread_exit(NULL);
}

void generateMatrix()
{
    // Generating random values in mat_A and mat_B
    for (size_t i = 0; i < MAX; i++)
    {
        for (size_t j = 0; j < MAX; j++)
        {
            mat_A[i][j] = rand() % 10;
            mat_B[i][j] = rand() % 10;
        }
    }
}

void sequential_approach()
{

    // defining variables to calculate time
    struct timespec start, end;

    // intializing thread id
    pthread_t thread_id;

    // storing start time
    clock_gettime(CLOCK_REALTIME, &start);

    pthread_create(&thread_id, NULL, &sequential_addition, NULL);

    // Waiting for join threads after compute
    pthread_join(thread_id, NULL);

    // storing end time
    clock_gettime(CLOCK_REALTIME, &end);

    // Display Addition of mat_A and mat_B
    // printf("\nSum of Matrix A and B:\n");
    // for (size_t i = 0; i < MAX; i++)
    // {
    //     for (size_t j = 0; j < MAX; j++)
    //     {
    //         printf("%d ", sum[i][j]);
    //     }
    //     printf("\n");
    // }

    // calculating time elapsed
    double time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

    printf("Time taken : %.10f seconds.\n", time_taken);
}
void parallel_approach()
{
    // defining variables to calculate time
    struct timespec start, end;

    // Maximum threads is equal to total core of system
    pthread_t thread[CORE];
    // storing start time
    clock_gettime(CLOCK_REALTIME, &start);

    // Creating threads equal
    // to core size and compute matrix row
    int step = 0;
    for (size_t i = 0; i < CORE; i++)
    {
        pthread_create(&thread[i], NULL, &parallel_addition, (void *)step);
        step++;
    }
    for (size_t i = 0; i < CORE; i++)
    {

        // Waiting for join threads after compute
        pthread_join(thread[i], NULL);
    }

    // storing end time
    clock_gettime(CLOCK_REALTIME, &end);

    // Display Addition of mat_A and mat_B
    // printf("\nSum of Matrix A and B:\n");

    // for (size_t i = 0; i < MAX; i++)
    // {

    //     for (size_t j = 0; j < MAX; j++)
    //     {

    //         printf("%d ", sum[i][j]);
    //     }

    //     printf("\n");
    // }
    // calculating time elapsed
    double time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

    printf("Time taken : %.10f seconds.\n", time_taken);
}