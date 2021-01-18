#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/**
 * Go Back N protocol.
 */
int main()
{
    // declaring variables
    int numOfFrames, windowSize;
    int count = 0, totalTransmissions = 0;
    int numOfTransInCurrentWindow = 0;
    //seeding random number generator
    srand(time(NULL));

    // gathering user input
    printf("Enter the number of frames: ");
    scanf("%d", &numOfFrames);
    printf("Enter the window size: ");
    scanf("%d", &windowSize);

    while (count <= numOfFrames)
    {
        numOfTransInCurrentWindow = 0;

        // loop for transmitting frames
        for (int j = count; j < count + windowSize && j <= numOfFrames; j++)
        {
            printf("Frame %d sent.\n", j);
            totalTransmissions++;
        }

        // loop for receiving acknowledgement
        for (int j = count; j < count + windowSize && j <= numOfFrames; j++)
        {
            // using flag to simulate whether frame is lost
            int flag = rand() % 2;

            // if flag is 0, implies acknowledgement received.
            if (!flag)
            {
                printf("Acknowledgement recieved for frame %d\n", j);
                numOfTransInCurrentWindow++;
            }
            else
            {
                printf("Frame %d not recevied. Retransmitting window.\n", j);
                break;
            }
        }
        printf("\n");
        count += numOfTransInCurrentWindow;
    }

    printf("total number of transmissions: %d\n", totalTransmissions);
}
