#include <stdio.h>
#include <pthread.h>

#define T 2
#define N 4

int A[100][100], B[100][100], C[100][100];
void *matrix_add(void *arg)
{
    int id = *(int *)arg;
    int i, j;

    for (i = id; i < N; i += T)
        for (j = 0; j < N; j++)
            C[i][j] = A[i][j] + B[i][j];

    pthread_exit(NULL);
}

int main()
{
    int i, j, m, n;
    int A[100][100], B[100][100], C[100][100];
    printf("enter the row of the matrix:");
    scanf("%d", &m);
    printf("enter the column of the matrix:");
    scanf("%d", &n);
    printf("Element of 1st matrix:\n");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d\t", rand() % 100);
        }
        printf("\n");
    }
    printf("enter the row of the matrix:");
    scanf("%d", &m);
    printf("enter the column of the matrix:");
    scanf("%d", &n);
    printf("Element of 2st matrix:\n");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d\t", rand() % 100);
        }
        printf("\n");
    }
    pthread_t thread[T];
    int tid[T];

    for (i = 0; i < m; i++)
    {
        tid[i] = i;
        pthread_create(&thread[i], NULL, matrix_add, &tid[i]);
    }

    for (i = 0; i < n; i++)
        pthread_join(thread[i], NULL);

    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            printf((j < n - 1) ? "%d " : "%d", C[i][j]);

    return 0;
}
