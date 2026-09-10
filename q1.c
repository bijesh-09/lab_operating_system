/*
Lab 1: Write a C program to demonstrate the use of getpid() and getppid() system calls.
*/

#include <stdio.h>
#include <unistd.h>

int main(){
    __pid_t process_id = getpid();
    __pid_t parent_process_id = getppid();

    printf("Current Process ID (PID): %d\n", process_id);
    printf("Parent Process ID (PPID): %d\n", parent_process_id);
    
    return 0;
}