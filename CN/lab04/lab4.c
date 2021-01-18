#include <stdio.h>

// struct containing information about routers
typedef struct node
{
    unsigned dist[20];
    unsigned via[20];
} Router;

int main()
{
    // declaring variables
    Router rt[20];
    int adjMat[20][20];
    int n, i, j, k, count = 0;

    // getting information from user
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    printf("Enter the cost matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &adjMat[i][j]);
            adjMat[i][i] = 0;
            rt[i].dist[j] = adjMat[i][j];
            rt[i].via[j] = j;
        }
    }

    // applying bellman ford algorithm
    do
    {
        count = 0;
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                for (k = 0; k < n; k++)
                    // relax edge if a better edge exists
                    if (rt[i].dist[j] > adjMat[i][k] + rt[k].dist[j])
                    {
                        rt[i].dist[j] = adjMat[i][k] + rt[k].dist[j];
                        rt[i].via[j] = k;
                        count++;
                    }

    } while (count != 0);

    // printing results
    for (i = 0; i < n; i++)
    {
        printf("\n\nState value for router %d : \n", i + 1);

        for (j = 0; j < n; j++)
        {
            printf("node %d via %d - Distance: %d\n", j + 1, rt[i].via[j] + 1, rt[i].dist[j]);
        }
    }
    printf("\n");
}
