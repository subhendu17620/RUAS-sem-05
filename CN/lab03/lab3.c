#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_NODES 1000

int main() {
    // declaring variables
    int x[MAX_NODES], y[MAX_NODES];
    int count = 0;
    int nodes, gridSize;

    float distance[MAX_NODES];
    float commRange = 0;
    char* inRange;

    // seeding random number generator
    srand(0);

    // gathering user input
    printf("Enter the number of nodes: ");
    scanf("%d", &nodes);
    printf("Enter the grid size: ");
    scanf("%d", &gridSize);
    printf("Enter the communication range: ");
    scanf("%f", &commRange);

    // generating random coordinates for nodes
    for (int i = 0; i < nodes; i++) {
        x[i] = rand() % (gridSize + 1);
        y[i] = rand() % (gridSize + 1);
    }

    printf("Nodes\tCoordinates\t\t\tWithin Range\tDistance between nodes\n");
    // generating neighbour table
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            // finding distance between ith node and jth node
            distance[count] = sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2));
            
            // checking if distance is within range
            inRange = (distance[count] <= commRange) ? "Yes" : "No";

            // printing result
            printf(
                "%d & %d\t(%d, %d) & (%d, %d)\t\t\t%s\t\t%.2f\n",
                i+1, j+1, x[i], y[i], x[j], y[j], inRange, 
                distance[count]
            );
            
            count++;
        }
    }
}
