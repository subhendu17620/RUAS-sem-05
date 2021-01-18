#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

/**
 * Selective Repeat protocol.
 */
int main()
{
    // declaring variables
    int numOfFrames, windowSize, flag;
    int count = 0, empty = 0, numOfAcks = 0;
    int *buffer;

    // seeding rand
    srand(time(NULL));

    // gathering input from user
    printf("Enter the number of frames: ");
    scanf("%d", &numOfFrames);
    printf("Enter the window size: ");
    scanf("%d", &windowSize);

    // mallocing buffer
    buffer = malloc(windowSize * sizeof(*buffer));
    memset(buffer, -1, windowSize * sizeof(*buffer));

    empty = windowSize;

    while (numOfAcks < numOfFrames)
    {
        // add frames to buffer
        for (int i = count + 1; i <= count + empty && i <= numOfFrames; i++)
        {
            for (int j = 0; j < windowSize; j++)
            {
                if (buffer[j] == -1)
                {
                    buffer[j] = i;
                    break;
                }
            }
        }

        // after filling buffer, number of empty slots is 0
        empty = 0;

        // transmitting frames
        for (int i = 0; i < windowSize; i++)
        {
            if (buffer[i] == -1)
                continue;
            printf("sent frame %d.\n", buffer[i]);
            if (buffer[i] > count)
                count = buffer[i];
        }
        printf("\n");

        // receiving acknowledgements
        for (int i = 0; i < windowSize; i++)
        {
            if (buffer[i] == -1)
                continue;
            flag = rand() % 2;

            // if the flag is 0, it means that acknowledgement has successfully been
            // received.
            if (!flag)
            {
                printf("Acknowledgement for frame %d received.\n", buffer[i]);
                buffer[i] = -1;
                empty++;
                numOfAcks++;
            }
            else
            {
                printf("Acknowledgement for frame %d not received.\n", buffer[i]);
            }
        }
    }
}
