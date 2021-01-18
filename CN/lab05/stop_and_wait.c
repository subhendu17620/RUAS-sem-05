#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/**
 * Stop and Wait Protocol.
 */
int main()
{
    // declaring variables
    int numOfFrames, flag;
    int count = 0;
    //seeding random number generator
    srand(time(NULL));

    // gathering user input
    printf("Enter the number of frames: ");
    scanf("%d", &numOfFrames);

    printf("Simulating Stop and Wait Protocol:\n");
    while (count < numOfFrames)
    {
        printf("Sending frame %d\n", count + 1);

        // using flag to simulate whether frame is lost
        flag = rand() % 2;

        // if flag is 0, transmission is successful
        if (!flag)
        {
            printf("Acknowledgement for frame %d recieved.\n\n", count + 1);
            count++;
        }
        else
        {
            printf("Acknowledgement for frame %d not recieved. "
                   "Retransmitting.\n",
                   count + 1);
        }
    }
}
