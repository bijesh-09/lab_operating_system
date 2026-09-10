#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int status;
    pid_t pid = fork();

    if (pid<0)
    {
        printf("Fork Failed!");
        return 1;
    }
    else if (pid == 0)
    {
        printf("\nChild Process\n");
        printf("Child PID: %d | Parent PID: %d\n",getpid(), getppid());
        printf("Child Process is working for 2sec...\n");
        sleep(2);
        exit(42); //custom exit condition
    }
    else{
        printf("\nParent Process\n");
        printf("Waiting for child process to terminate...\n");
        
        pid_t terminated_child_pid = wait(&status); //status is filled with exitcode and flags of child process
        
        printf("\nResuming parent process since child process is terminated\n");
        printf("Terminated Child PID: %d | Parent PID: %d\n",terminated_child_pid, getpid());

        if (WIFEXITED(status))
        {
            printf("Child process normally exited with exit code: %d", WEXITSTATUS(status));
        }
        else{
            printf("Child exited abnormally");
        }
        
        
    }
    
    
    return 0;
}