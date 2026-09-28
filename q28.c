// Lab 28: Menu-Driven Operating System Simulator
// Launches the earlier lab programs (q6..q24) based on the chosen menu option.
// Run this from the os_lab folder (where q*.c files and bin/ are).

#include <stdio.h>
#include <stdlib.h>

#define SIZE 300

// One menu entry: text shown to the user + source file name (without .c)
typedef struct {
    const char *label;
    const char *file;
} Program;

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Compile <file>.c into bin/<file>, and run it only if compilation succeeded
void runProgram(const char *file) {
    char cmd[SIZE];
    snprintf(cmd, SIZE, "mkdir -p bin && gcc %s.c -o bin/%s && ./bin/%s",
             file, file, file);

    printf("\n>>> Running %s.c ...\n", file);
    printf("--------------------------------------------\n");
    int status = system(cmd);
    printf("\n--------------------------------------------\n");

    if (status != 0)
        printf(">>> Program exited with an error (or failed to compile).\n");
}

// Generic sub-menu: shows the list, runs the chosen program
void subMenu(const char *title, Program list[], int count) {
    int choice;
    while (1) {
        printf("\n===== %s =====\n", title);
        for (int i = 0; i < count; i++)
            printf("%d. %s\n", i + 1, list[i].label);
        printf("0. Back to main menu\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {   // user typed a non-number
            clearBuffer();
            printf("Invalid input!\n");
            continue;
        }
        clearBuffer();

        if (choice == 0) return;
        if (choice < 1 || choice > count) {
            printf("Invalid choice!\n");
            continue;
        }
        runProgram(list[choice - 1].file);
    }
}

int main() {
    Program cpu[] = {
        {"FCFS Scheduling",        "q6"},
        {"SJF Scheduling",         "q7a"},
        {"SRTF Scheduling",        "q7b"},
        {"Priority Scheduling",    "q8"},
        {"Round Robin Scheduling", "q9"}
    };

    Program memory[] = {
        {"First Fit / Best Fit / Worst Fit", "q15"}
    };

    Program page[] = {
        {"FIFO Page Replacement",            "q16"},
        {"LRU and Optimal Page Replacement", "q17and18"},
        {"Second Chance Page Replacement",   "second_chance"}
    };

    Program disk[] = {
        {"FCFS Disk Scheduling",   "q19"},
        {"SSTF Disk Scheduling",   "q20"},
        {"SCAN Disk Scheduling",   "q21"},
        {"C-SCAN Disk Scheduling", "q22"},
        {"LOOK Disk Scheduling",   "q23"},
        {"C-LOOK Disk Scheduling", "q24"}
    };

    int choice;
    while (1) {
        printf("\n########################################\n");
        printf("#      OPERATING SYSTEM SIMULATOR      #\n");
        printf("########################################\n");
        printf("1. CPU Scheduling\n");
        printf("2. Memory Allocation\n");
        printf("3. Page Replacement\n");
        printf("4. Disk Scheduling\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            clearBuffer();
            printf("Invalid input!\n");
            continue;
        }
        clearBuffer();

        switch (choice) {
            case 1: subMenu("CPU SCHEDULING",   cpu,    sizeof(cpu)    / sizeof(cpu[0]));    break;
            case 2: subMenu("MEMORY ALLOCATION", memory, sizeof(memory) / sizeof(memory[0])); break;
            case 3: subMenu("PAGE REPLACEMENT", page,   sizeof(page)   / sizeof(page[0]));   break;
            case 4: subMenu("DISK SCHEDULING",  disk,   sizeof(disk)   / sizeof(disk[0]));   break;
            case 5: printf("Exiting simulator. Bye!\n"); return 0;
            default: printf("Invalid choice!\n");
        }
    }
}