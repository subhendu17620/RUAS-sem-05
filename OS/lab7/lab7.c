#include <stdio.h>
#include <stdbool.h>

#define NUM_PROCESSES 5
#define NUM_RESOURCE_CLASSES 3

bool isStateSafe(int[], int[], int[][NUM_RESOURCE_CLASSES], int[][NUM_RESOURCE_CLASSES], int[]);

int main(int argc, char *argv[])
{
    // defining variable to store the process ids
    int processes[] = {0, 1, 2, 3, 4};

    // Available instances of resources
    int avail[] = {3, 3, 2};

    // Maximum R that can be allocated
    // to processes
    int maxm[][NUM_RESOURCE_CLASSES] = {{7, 5, 3},
                                        {3, 2, 2},
                                        {9, 0, 2},
                                        {2, 2, 2},
                                        {4, 3, 3}};

    // Resources allocated to processes
    int allot[][NUM_RESOURCE_CLASSES] = {{0, 1, 0},
                                         {2, 0, 0},
                                         {3, 0, 2},
                                         {2, 1, 1},
                                         {0, 0, 2}};

    // declaring variable to store processes sequence
    int seq[NUM_PROCESSES];

    bool res = isStateSafe(processes, avail, maxm, allot, seq);

    if (res)
    {
        printf("This state is safe. The sequence that leads to completetion of all processes is:\n");
        for (int i = 0; i < NUM_PROCESSES; i++)
            printf("%d ", seq[i]);
        printf("\n");
    }
}

/**
 * Checks if the given state is a safe state or not.
 * @param processes the process ids.
 * @param availableVector the vector containing the amount of resources available per class.
 * @param maxRequired contains the maximum number of resources required to complete 
 * (for each process).
 * @param currentAlloc contains the number of resources held by each process.
 * @param seq to store the sequence of processes that need to be executed that lead to
 * completion.
 * @return true, if state is safe, false otherwise.
 */
bool isStateSafe(int processes[], int availableVector[], int maxRequired[][NUM_RESOURCE_CLASSES],
                 int currentAlloc[][NUM_RESOURCE_CLASSES], int seq[])
{

    // declaring request matrix
    int requestMatrix[NUM_PROCESSES][NUM_RESOURCE_CLASSES];
    // initializing all processes as not finished
    bool finished[NUM_PROCESSES] = {0};
    // variable to store copy of availableVector
    int availCopy[NUM_RESOURCE_CLASSES];
    // variable to keep track of loop
    int count = 0;

    // finding the request matrix
    for (int i = 0; i < NUM_PROCESSES; i++)
        for (int j = 0; j < NUM_RESOURCE_CLASSES; j++)
            requestMatrix[i][j] = maxRequired[i][j] - currentAlloc[i][j];

    // creating copy
    for (int i = 0; i < NUM_RESOURCE_CLASSES; i++)
        availCopy[i] = availableVector[i];

    // while all processes are not finished
    while (count < NUM_PROCESSES)
    {
        bool isSafe = false;
        // for every process, do
        for (int i = 0; i < NUM_PROCESSES; i++)
        {
            // if process is not finished, do
            if (finished[i] == 0)
            {
                int j;
                // checking if process i can be completed with the
                // available resources
                for (j = 0; j < NUM_RESOURCE_CLASSES; j++)
                    if (requestMatrix[i][j] > availCopy[j])
                        // process cannot be completed, break out of loop
                        break;

                // if it was able to be completed, do
                if (j == NUM_RESOURCE_CLASSES)
                {
                    // freeing resources
                    for (int k = 0; k < NUM_RESOURCE_CLASSES; k++)
                        availCopy[k] += currentAlloc[i][k];

                    // adding process to sequence
                    seq[count++] = processes[i];

                    // marking process as finished
                    finished[i] = 1;

                    // a safe state is found
                    isSafe = true;
                }
            }
        }

        // if no safe state was found, return false
        if (isSafe == false)
            return false;
    }

    return true;
}
