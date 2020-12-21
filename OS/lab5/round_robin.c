#include <stdio.h>
#include <stdbool.h>

void getTAT(int processes[], int n, int bt[], int wt[], int tat[]);
void getWT(int processes[], int n, int bt[], int wt[], int quantum);
void getAvgTime(int processes[], int n, int bt[], int quantum);

int main()
{
    int n;
    printf("Enter no of processes:-");
    scanf("%d", &n);

    int processes[n];
    int burst_time[n];

    // Time quantum
    int quantum;
    printf("Enter Time Quantam:-");
    scanf("%d", &quantum);
    printf("Enter burst times:- \n");
    for (size_t i = 0; i < n; i++)
    {
        processes[i] = i;
        scanf(" %d", &burst_time[i]);
    }

    getAvgTime(processes, n, burst_time, quantum);
    return 0;
}

void getWT(int processes[], int n, int bt[], int wt[], int quantum)
{
    int rem_bt[n];
    for (int i = 0; i < n; i++)
        rem_bt[i] = bt[i];

    int t = 0;
    while (true)
    {
        bool done = true;
        for (int i = 0; i < n; i++)
        {
            if (rem_bt[i] > 0)
            {
                done = false;
                if (rem_bt[i] > quantum)
                {
                    t += quantum;
                    rem_bt[i] -= quantum;
                }
                else
                {
                    t = t + rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }

        if (done == true)
            break;
    }
}

void getTAT(int processes[], int n, int bt[], int wt[], int tat[])
{
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}
void getAvgTime(int processes[], int n, int bt[], int quantum)
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    getWT(processes, n, bt, wt, quantum);
    getTAT(processes, n, bt, wt, tat);

    printf("Prs \t BT \t WT \t TAT\n");

    // Calculate total WT and Total TAT
    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf("%d \t %d \t %d \t %d \n", i + 1, bt[i], wt[i], tat[i]);
    }
    printf("Average waiting time = %0.3f", (float)total_wt / (float)n);
    printf("\nAverage turn around time = %0.3f", (float)total_tat / (float)n);
}