/*
Lab 8: Implement the Priority Scheduling Algorithm(for non preemptive processes).
*/

#include <stdio.h>

struct Process {
    int pid;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
};

void sortProcessesByPriority(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].priority > p[j + 1].priority) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void calculateTimes(struct Process p[], int n) {
    p[0].waiting_time = 0;
    p[0].turnaround_time = p[0].burst_time;

    for (int i = 1; i < n; i++) {
        p[i].waiting_time = p[i - 1].turnaround_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
    }
}

void displayResults(struct Process p[], int n) {
    float total_wt = 0, total_tat = 0;

    printf("\nProcess ID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    printf("-------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               p[i].pid, p[i].burst_time, p[i].priority, p[i].waiting_time, p[i].turnaround_time);
    }

    printf("-------------------------------------------------------------------------\n");
    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter Burst Time for Process P%d: ", p[i].pid);
        scanf("%d", &p[i].burst_time);
        printf("Enter Priority for Process P%d (lower number = higher priority): ", p[i].pid);
        scanf("%d", &p[i].priority);
    }

    sortProcessesByPriority(p, n);
    calculateTimes(p, n);
    displayResults(p, n);

    return 0;
}