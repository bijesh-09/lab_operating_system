/*
Lab 9: Implement the Round Robin Scheduling Algorithm
*/
#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], rem_bt[n], ct[n], tat[n], wt[n];
    bool in_queue[n];

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Process %d (Arrival Time & Burst Time): ", pid[i]);
        scanf("%d %d", &at[i], &bt[i]);
        rem_bt[i] = bt[i];
        in_queue[i] = false;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    // Queue implementation using a simple array
    int queue[100];
    int front = 0, rear = 0;

    int current_time = 0;
    int completed_count = 0;

    // Check for any processes arriving at time 0
    for (int i = 0; i < n; i++) {
        if (at[i] <= current_time && !in_queue[i]) {
            queue[rear++] = i;
            in_queue[i] = true;
        }
    }

    while (completed_count < n) {
        // If queue is empty, advance time until a process arrives
        if (front == rear) {
            current_time++;
            for (int i = 0; i < n; i++) {
                if (at[i] <= current_time && !in_queue[i] && rem_bt[i] > 0) {
                    queue[rear++] = i;
                    in_queue[i] = true;
                }
            }
            continue;
        }

        // Pop the front process from queue
        int curr = queue[front++];

        // Determine execution time (either quantum or remaining burst time)
        int exec_time = (rem_bt[curr] < tq) ? rem_bt[curr] : tq;

        // Execute process
        rem_bt[curr] -= exec_time;
        current_time += exec_time;

        // 1. ADD NEW ARRIVALS FIRST: Check if any unqueued processes arrived during this execution window
        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && !in_queue[i] && rem_bt[i] > 0) {
                queue[rear++] = i;
                in_queue[i] = true;
            }
        }

        // 2. RE-QUEUE CURRENT PROCESS SECOND: If current process is not done, put it back into queue
        if (rem_bt[curr] > 0) {
            queue[rear++] = curr;
        } else {
            // Process finished
            ct[curr] = current_time;
            tat[curr] = ct[curr] - at[curr];
            wt[curr] = tat[curr] - bt[curr];
            completed_count++;
        }
    }

    // Display Results
    float total_tat = 0, total_wt = 0;
    printf("\n-------------------------------------------------------------------\n");
    printf("PID\tArrival T\tBurst T\tCompletion T\tTAT\tWT\n");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        total_tat += tat[i];
        total_wt += wt[i];
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t%d\n", 
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("-------------------------------------------------------------------\n");
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
    printf("Average Waiting Time    = %.2f\n", total_wt / n);

    return 0;
}