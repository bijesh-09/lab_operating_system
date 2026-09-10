/*
Lab 6: Implement the First Come First Serve (FCFS) CPU Scheduling Algorithm.
*/


#include<stdio.h>
#include<stdbool.h>
#define max(a, b) ((a) > (b) ? (a) : (b))   

int main(){
    //p=process, at=arrivalTime, bt=burst/executeTime, tat=turnAroundTime, wt=WaitingTime
    int  p[10], at[10], bt[10], ct[10], tat[10], wt[10], n;
    float avg_tat=0.0, avg_wt=0.0;

    printf("\nEnter no. of processes: ");
    scanf("%d",&n);

    printf("\nEnter | PID | Arrival Time(secs) | Burst Time(secs) | of each processes:\n ");
    for (int i = 0; i < n; i++)
    {
        printf("%d. ",i+1);
        scanf("%d %d %d", &p[i], &at[i], &bt[i]);
    }
    
    
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                
                int temp = p[j+1];
                p[j+1] = p[j];
                p[j] = temp;
                
                temp = at[j+1];
                at[j+1] = at[j];
                at[j] = temp;

                temp = bt[j+1];
                bt[j+1] = bt[j];
                bt[j] = temp;

                swapped = true;
            }
        }
        // If no two elements were swapped, then break
        if (!swapped)
            break;
    }
    
    //calculate 1st ct
    ct[0] = at[0] + bt[0];

    /* calculating ct from 2nd to n processes */
    for (int i = 1; i < n; i++)
    {
        //max chooses at[i] when cpu is idle and new process arrives
        // chooses ct[i-1] if process arrives before or right when previous process completes
        ct[i] = max(ct[i-1], at[i]) + bt[i]; 
    }

    //calculating tat and wt of each process
    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    //avgs
    avg_tat /= n;
    avg_wt /= n;

    printf("\nFRIST COME FIRST SERVE (FCFS)\n");
    printf("\n|PID|ArrivalT|BurstT|TAT|WaitingT|CompletionT|\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], tat[i], wt[i], ct[i]);
    }
    
    printf("\nAvg TurnAround Time = %.2f | Avg Waiting Time = %.2f\n", avg_tat, avg_wt);

    
    return 0;
}