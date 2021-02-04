#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void best_fit(int*, int, int*, int);
void first_fit(int*, int, int*, int);
void worst_fit(int*, int, int*, int);
void disp(int*, int*, int);

int main() {
    // declaring input variables
    int m, n;

    // getting number of blocks from user
    printf("Enter the number of blocks: ");
    scanf("%d", &m);

    // getting block sizes from user
    int blockSizes[m];
    for (int i = 0; i < m; i++) {
        printf("Enter size of block %d: ", i+1);
        scanf("%d", &blockSizes[i]);
        getchar();
    }

    // getting number of processes from user
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);

    // getting process sizes from user
    int processSizes[n];
    for (int i = 0; i < n; i++) {
        printf("Enter size of process %d: ", i+1);
        scanf("%d", &processSizes[i]);
        getchar();
    }

    // creating copy of blockSizes to be passed to the function 
    // and calling best fit
    int* blockSizesCopy = malloc(sizeof(*blockSizesCopy) * m);
    memcpy(blockSizesCopy, blockSizes, sizeof(blockSizes));
    best_fit(blockSizesCopy, m, processSizes, n);

    // creating copy of blockSizes to be passed to the function 
    // and calling first fit
    blockSizesCopy = malloc(sizeof(*blockSizesCopy) * m);
    memcpy(blockSizesCopy, blockSizes, sizeof(blockSizes));
    first_fit(blockSizesCopy, m, processSizes, n);

    // creating copy of blockSizes to be passed to the function 
    // and calling worst fit
    blockSizesCopy = malloc(sizeof(*blockSizesCopy) * m);
    memcpy(blockSizesCopy, blockSizes, sizeof(blockSizes));
    worst_fit(blockSizesCopy, m, processSizes, n);
}

void best_fit(int* blockSizes, int m, int* processSizes, int n) {
    // defining variable to store the allocation
    int allocs[n]; 
  
    // initializing allocs to be -1 
    memset(allocs, -1, sizeof(allocs)); 
  
    // going through all the processes
    for (int i=0; i<n; i++) { 
        int index = -1;

        // going through all the blocks
        for (int j=0; j<m; j++) { 
            // if a process can fit in the block
            if (blockSizes[j] >= processSizes[i]) { 
                if (index == -1) 
                    index = j; 
                // if there is a better fitting block
                else if (blockSizes[index] > blockSizes[j]) 
                    index = j; 
            } 
        } 
  
        // if we found the best block 
        if (index != -1) { 
            // allocate block j to p[i] process 
            allocs[i] = index; 
  
            // Reduce available memory in this block. 
            blockSizes[index] -= processSizes[i]; 
        } 
    } 

    // printing results
    printf("\nBest fit results:\n");
    disp(processSizes, allocs, n);
}

void first_fit(int* blockSizes, int m, int* processSizes, int n) {
    // defining variable to store the allocated processes
    int allocs[n]; 
  
    // initializing allocation to -1
    memset(allocs, -1, sizeof(allocs)); 
  
    // for all the processes 
    for (int i = 0; i < n; i++) { 
        // for all the blocks
        for (int j = 0; j < m; j++) { 
            // if the process can fit in the block
            if (blockSizes[j] >= processSizes[i]) { 
                // allocate block to process 
                allocs[i] = j; 
  
                // Reduce available memory in this block. 
                blockSizes[j] -= processSizes[i]; 
                break; 
            } 
        } 
    } 
    
    // printing results
    printf("\nFirst fit results:\n");
    disp(processSizes, allocs, n);  
}

void worst_fit (int* blockSizes, int m, int* processSizes, int n) {
    // defining variable to store the allocation
    int allocs[n]; 
  
    // initializing allocs to be -1 
    memset(allocs, -1, sizeof(allocs)); 
  
    // going through all the processes
    for (int i=0; i<n; i++) { 
        int index = -1;

        // going through all the blocks
        for (int j=0; j<m; j++) { 
            // if a process can fit in the block
            if (blockSizes[j] >= processSizes[i]) { 
                if (index == -1) 
                    index = j; 
                // if there is a better fitting block
                else if (blockSizes[index] < blockSizes[j]) 
                    index = j; 
            } 
        } 
  
        // if we found the best block 
        if (index != -1) { 
            // allocate block j to p[i] process 
            allocs[i] = index; 
  
            // Reduce available memory in this block. 
            blockSizes[index] -= processSizes[i]; 
        } 
    } 

    // printing results
    printf("\nWorst fit results\n");
    disp(processSizes, allocs, n);
}

void disp(int* processSizes, int* allocs, int numOfProcesses) {
    printf("Process No.\tProcess size\tBlock no.\n");
    for(int i = 0; i < numOfProcesses; i++) {
        printf("%d\t\t%d\t\t", i+1, processSizes[i]);
        if (allocs[i] != -1)
            printf("%d\n", allocs[i]+1);
        else
            printf("Not allocated\n");
    }
}

