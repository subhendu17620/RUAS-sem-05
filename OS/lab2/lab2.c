#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for system calls

int main()
{

    printf("child pid = %d from parent pid = %d \n", getpid(), getppid());
    // creating 4 process from 1 same parent
    for (int i = 0; i < 4; i++) // 4 processes
    {
        if (fork() == 0)
        {
            printf("child pid = %d from parent pid = %d \n", getpid(), getppid());
            exit(0);
        }
    }
    return (EXIT_SUCCESS);
}
