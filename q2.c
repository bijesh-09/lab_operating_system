/*
Lab 2: Write a C program to create a child process using fork() and 
demonstrate parent-child process execution.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    // fork() clones your running program into two separate copies in RAM at this exact line of code.
    pid_t pid = fork();

    /*
    To help your code figure out which copy it is (the Parent or the Child), 
    the os gives a different return value to each process from that same fork() call.
    The Return Values of fork()
    To the Child process: fork() returns 0.
    To the Parent process: fork() returns the actual PID of the new child process
    */
    if (pid < 0) {
        // fork() returns a negative value if process creation fails
        fprintf(stderr, "Fork failed!\n");
        return 1;
    } 
    else if (pid == 0) {
        // Child process receives 0 from fork()
        printf("--- Child Process ---\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID (from Child's perspective): %d\n\n", getppid());
    } 
    else {
        // Parent process receives the actual PID of the newly created child
        printf("--- Parent Process ---\n");
        printf("Parent PID: %d\n", getpid());
        printf("Created Child PID: %d\n\n", pid);
    }

    return 0;
}