#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *Threadprocess(int a[])
{
    int sum = 0;

    for (int i = 0; i < 5; i++)
    {
        sum = sum + a[i];
    }
    pthread_exit(sum);

    return NULL;
}
int main(int argc, char *argv)
{

    int *exitstatus1;
    int *exitstatus2;

    pthread_t thread_1;
    pthread_t thread_2;

    int student1[] = {7, 7, 6, 4, 9};
    int student2[] = {5, 6, 8, 8, 7};

    pthread_create(&thread_1, NULL, Threadprocess, student1);
    pthread_create(&thread_2, NULL, Threadprocess, student2);

    pthread_join(thread_1, (void *)&exitstatus1);
    pthread_join(thread_2, (void *)&exitstatus2);

    printf("student 1 total marks : %d \n", exitstatus1);

    printf("student 2 total marks : %d \n", exitstatus2);
    printf("Student 1 scored higher marks ");

    if (*exitstatus1 > *exitstatus2)
        printf("Student 1 scored higher marks ");
    else
        printf("Student 2 scored higher marks ");

    return (EXIT_SUCCESS);
}