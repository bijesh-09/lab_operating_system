/*
Lab 5: Write a C program to demonstrate Inter-Process Communication (IPC) using pipe().
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(){

    int pipefds[2]; //file descriptor of pipe for read end at 0th index and write end at 1th index
    int pid;
    char read_msg[100];
    char write_msg[100] = "Hello from Child Process via Pipe!";
    
    if (pipe(pipefds) == -1)
    {
        printf("Pipe creation failed!");
        return 1;
    }
    
    pid = fork();
    
    if (pid < 0)
    {
        printf("Fork failed!");
        return 1;
    }
    else if (pid == 0)
    {
        printf("\nChild Process\n");
        close(pipefds[0]); //closing unused read end of child process to prevent file descriptor leaks
        printf("Child Process PID: %d | Parent Process: %d\n", getpid(), getppid());
        
        printf("Child Process is writing msg to pipe...\n");
        write(pipefds[1], write_msg, sizeof(write_msg));
        close(pipefds[1]);
        
    }
    else{
        printf("\nParent Process\n");
        printf("Child Process PID: %d | Parent Process: %d\n",pid, getpid());
        close(pipefds[1]);
        
        printf("\nParent Process is waiting for message from pipe sent by child process...\n");
        read(pipefds[0], read_msg, sizeof(read_msg));
        printf("\nMessage received by parent from child: \"%s\"\n",read_msg);

        close(pipefds[0]);
        
        
    }
    
    
    

    return 0;
}