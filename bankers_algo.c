#include <stdio.h>
#include <stdbool.h>

bool sys_safe_state_checker(int alloc[5][3], int max[5][3], int need[5][3], int avail[3])
{

    // P0, P1, P2, P3, P4 are the names of Process
    int n = 5, r = 3; // n = no. of processes, r = no. of resources

    // copying avail cuz array are passed by ref in C, and we are pretending to finish processes to check whether system is safe or not
    int simulated_avail[r];
    for (int i = 0; i < r; i++)
    {
        simulated_avail[i] = avail[i];
    }

    int finished[n], finished_counter = 0;
    int safe_seq[n], safe_seq_idx = 0;

    // initially assuming all processes arent finished yet
    for (int i = 0; i < n; i++)
    {
        finished[i] = 0;
    }

    for (int count = 0; count < n; count++)
    {
        for (int i = 0; i < n; i++)
        {
            if (finished[i] == 0)
            {
                int avail_insufficient_flag = 0;
                for (int j = 0; j < r; j++)
                {
                    if (need[i][j] > simulated_avail[j])
                    {
                        avail_insufficient_flag = 1;
                        break;
                    }
                }

                if (avail_insufficient_flag == 0)
                {
                    safe_seq[safe_seq_idx++] = i;
                    for (int k = 0; k < r; k++)
                    {
                        simulated_avail[k] += alloc[i][k];
                    }
                    finished[i] = 1;
                    finished_counter++;
                }
            }
        }

        if (finished_counter == n)
        {
            return 1; // System is in safe state
        }
    }
    return 0; // System is not in safe state
}

int request_resources(int alloc[5][3], int max[5][3], int need[5][3], int avail[3], int pid, int req[3])
{

    // P0, P1, P2, P3, P4 are the names of Process
    int n = 5, r = 3; // n = no. of processes, r = no. of resources

    // Checking if request is less than need
    for (int j = 0; j < r; j++)
    {
        if (req[j] > (need[pid][j]))
        {
            printf("Error: Process P%d{%d, %d, %d} has exceeded its maximum claim\n", pid, req[0], req[1], req[2]);
            return 0;
        }
    }

    // Checking if request is less than available
    for (int j = 0; j < r; j++)
    {
        if (req[j] > avail[j])
        {
            printf("Error: Resources are not available for Process P%d{%d, %d, %d}\n", pid, req[0], req[1], req[2]);
            return 0;
        }
    }

    // 3. Pretend to allocate resources
    for (int j = 0; j < r; j++)
    {
        avail[j] -= req[j];
        alloc[pid][j] += req[j];
        need[pid][j] -= req[j];
    }

    // 4. Test if the NEW pretend state is safe
    if (sys_safe_state_checker(alloc, max, need, avail))
    {
        printf("Success: Request granted to Process P%d{%d, %d, %d}. System remains in safe state.\n", pid, req[0], req[1], req[2]);
        printf("Updated Available Resources:\n");
        for (int j = 0; j < r; j++)
        {
            printf("%d ", avail[j]);
        }
        printf("\n");
        return 1;
    }
    else
    {
        // Rollback state changes if unsafe
        for (int j = 0; j < r; j++)
        {
            avail[j] += req[j];
            alloc[pid][j] -= req[j];
            need[pid][j] += req[j];
        }
        printf("Error: Request denied for Process P%d{%d, %d, %d}. System would enter an unsafe state!\n", pid, req[0], req[1], req[2]);
        return 0;
    }
}

int main()
{

    // Initial snapshot of the system --------------------------

    // This is Allocation Matrix
    int alloc[5][3] = {
        {0, 1, 0}, // P0
        {2, 0, 0}, // P1
        {3, 0, 2}, // P2
        {2, 1, 1}, // P3
        {0, 0, 2}  // P4
    };

    // MAX Matrix
    int max[5][3] = {
        {7, 5, 3}, // P0
        {3, 2, 2}, // P1
        {9, 0, 2}, // P2
        {2, 2, 2}, // P3
        {4, 3, 3}  // P4
    };

    int avail[3] = {3, 3, 2}; // These are Available Resources
    int need[5][3];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    //-------------------------------------------------------------

    printf("Initial snapshot of the system:\n");
    printf("Allocation Matrix:\n");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", alloc[i][j]);
        }
        printf("\n");
    }
    printf("Max Matrix:\n");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }
    printf("Need Matrix:\n");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    printf("Available Resources:\n");
    for (int j = 0; j < 3; j++)
    {
        printf("%d ", avail[j]);
    }
    printf("\n");

    printf("\nChecking if the current system state is in safe state or not...\n");
    if (sys_safe_state_checker(alloc, max, need, avail))
    {
        printf("Current system state is in safe state\n");
    }
    else
    {
        printf("Current system state is not in safe state\n");
    }

    printf("\nProcesses are requesting resources...\n");

    request_resources(alloc, max, need, avail, 0, (int[]){8, 0, 0});
    request_resources(alloc, max, need, avail, 2, (int[]){5, 0, 0});
    request_resources(alloc, max, need, avail, 1, (int[]){0, 2, 0});
    request_resources(alloc, max, need, avail, 0, (int[]){0, 2, 0});
    request_resources(alloc, max, need, avail, 4, (int[]){0, 1, 0});

    printf("\nRe-checking if the current system state is in safe state or not...\n");
    if (sys_safe_state_checker(alloc, max, need, avail))
    {
        printf("Current system state is in safe state\n");
    }
    else
    {
        printf("Current system state is not in safe state\n");
    }
    return 0;
}