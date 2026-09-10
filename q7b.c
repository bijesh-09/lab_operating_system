/*
Lab 7.2: Implement the Shortest Remaining Time First (SRTF) CPU Scheduling Algorithm.
*/

#include<stdio.h>  

int main(){
    //p=process, at=arrivalTime, bt=burst/executeTime, tat=turnAroundTime, wt=WaitingTime
    int  p[10], at[10], bt[10], ct[10], tat[10], wt[10], original_bt[10];
    int n, count = 0, end = 0, smallest;
    float avg_tat=0.0, avg_wt=0.0;
    
    
    printf("\nEnter no. of processes: ");
    scanf("%d",&n);
    
    printf("\nEnter | PID | Arrival Time(secs) | Burst Time(secs) | of each processes:\n ");
    for (int i = 0; i < n; i++)
    {
        printf("%d. ",i+1);
        scanf("%d %d %d", &p[i], &at[i], &bt[i]);
        original_bt[i] = bt[i]; //preserving original_bt value since bt[i] can decrement as the process executes further
    }
    
    smallest = 9;//making smallest last index
    bt[smallest] = 9999;// making bt of last index as dummy so that any process's bt can easily be less than this value
    
    for (int time = 0; count != n; time++) //time works as system clock here
    {
        smallest = 9;//resetting smallest everytime to compare processes with bt[smallest]=9999

        //find the process with smallest remaining time among the processes arrived within current "time" var's value
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && bt[i] < bt[smallest] && bt[i] > 0)
            {
                smallest = i;
            }
        }

        //execute the smallest burst time process and decrement its bt by unit
        bt[smallest]--;

        //if the current smallest burst time process is finished executing
        if (bt[smallest] == 0)
        {
            count++; // count represent total no. of process finished
            ct[smallest] = time + 1; // (time + 1) represents time tick at which the that process finished

            //calculating tat and wt of each process
            tat[smallest] = ct[smallest] - at[smallest];
            wt[smallest] = tat[smallest] - original_bt[smallest];
        }
        
        
    }
    
    //avgs
    for (int i = 0; i < n; i++)
    {
        avg_tat += tat[i];
        avg_wt += wt[i];
    }
    avg_tat /= n;
    avg_wt /= n;

    printf("\nSHORTEST REMAINING TIME FIRST (SRTF)\n");

    printf("\n|PID|ArrivalT|BurstT|TAT|WaitingT|CompletionT|\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], original_bt[i], tat[i], wt[i], ct[i]);
    }
    
    printf("\nAvg TurnAround Time = %.2f | Avg Waiting Time = %.2f\n", avg_tat, avg_wt);

    
    return 0;
}