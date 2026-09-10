/*
Lab 7.1: Implement the Shortest Job First (SJF) CPU Scheduling Algorithm.
*/

#include<stdio.h>
#include<stdbool.h>  

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort(int p[], int at[], int bt[], int n){
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {

            //sort based on arrival time
            if (at[j] > at[j + 1]) {
                
                swap(&p[j], &p[j+1]);
                swap(&at[j], &at[j+1]);
                swap(&bt[j], &bt[j+1]);

                swapped = true;
            }
            //sort based on burst time if arrival time of two processes are equal
            else if (at[j] == at[j + 1])
            {
                if (bt[j] > bt[j+1])
                {
                    swap(&p[j], &p[j+1]);
                    swap(&at[j], &at[j+1]);
                    swap(&bt[j], &bt[j+1]);
                }
                
            }
            
        }
        // If no two elements were swapped, then break
        if (!swapped)
            break;
    }
}

int main(){
    //p=process, at=arrivalTime, bt=burst/executeTime, tat=turnAroundTime, wt=WaitingTime
    int  p[10], at[10], bt[10], ct[10], tat[10], wt[10];
    int n, pos, min = 1000;
    float avg_tat=0.0, avg_wt=0.0;

    printf("\nEnter no. of processes: ");
    scanf("%d",&n);

    printf("\nEnter | PID | Arrival Time(secs) | Burst Time(secs) | of each processes:\n ");
    for (int i = 0; i < n; i++)
    {
        printf("%d. ",i+1);
        scanf("%d %d %d", &p[i], &at[i], &bt[i]);
    }
    
    //sort the processes based on arrival time otherwise on burst time if arrival time of two processes are equal
    sort(p,at,bt,n);
    
    //---------------------------------------------------------------------------------------------------------------
    /*
    -> calc ct of (i-1)th process 
    -> find the process with shortest burst time among the process arrived in ct[i-1]
    -> replace that process in i^th position
    -> calc ct of ith process, reset min to 1000 for next iter
    -> repeat above process for each iter
    */
    
    //calculate ct of initial non-preemptive process
    // ct[i-1] = ct[0] for starting at i = 1
    ct[0] = at[0] + bt[0];

    for (int i = 1; i < n; i++)
    {
        
        for (int j = i; j < n; j++)
        {
            // -> only look for processes that arrive within ct of currently executed process i.e. (i-t)th process
            if (at[j] <= ct[i-1]) 
            {

                if (bt[j] < min)
                {
                    min = bt[j]; //update min with each new lesser value of bt[j] when found
                    pos = j; // mark the shortest process's index during the loop
                }
                
            }    
        }

        // -> replace that process in i^th position
        swap(&p[i], &p[pos]);
        swap(&at[i], &at[pos]);
        swap(&bt[i], &bt[pos]);
        
        // -> calc ct of ith process, reset min to 1000 for next iter
        ct[i] = ct[i-1] + bt[i]; //here we dont ve to account for cpu idle time since, we are sorting based on only the processes that arrived within c[i-1] time
        min = 1000; //resetting min for next iter
    }
    //---------------------------------------------------------------------------------------------------------------------


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

    printf("\nSHORTEST JOB FRIST (SJF)\n");
    printf("\n|PID|ArrivalT|BurstT|TAT|WaitingT|CompletionT|\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], tat[i], wt[i], ct[i]);
    }
    
    printf("\nAvg TurnAround Time = %.2f | Avg Waiting Time = %.2f\n", avg_tat, avg_wt);

    
    return 0;
}