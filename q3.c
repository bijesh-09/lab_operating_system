/*
Lab 3: Write a C program to create multiple child processes and display their Process IDs.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){

    pid_t pids[3];
    int child_idx = -1;

    for (int i = 0; i < 3; i++) //forking 3 children only for main parent
    {
        pids[i] = fork();

        if (pids[i] < 0)
        {
            printf("Unable to fork child process%d\n", i+1);
        }
        else if (pids[i] == 0)
        {
            child_idx = i+1;
            break; // break immedaitely so that child process doesnt loop and fork its childs and grandchilds   
        }
    }

    if (child_idx > 0)
    {
        printf("Child process: %d\n", child_idx);
        printf("Child PID: %d | Parent PID: %d\n", getpid(), getppid());
    }
    else{
        //pause main parent until child processes terminates, NULL means main parent will not do anything with exit codes of childs 
        for (int i = 0; i < 3; i++)
        {
            wait(NULL); 
        }
        
        printf("\nMain Parent PID: %d", getpid());
        for (int i = 0; i < 3; i++)
        {
            printf("\nChild %d PID: %d", i+1, pids[i]);
        }
        
    }
    return 0;
}