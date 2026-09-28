// Lab 26: Write a C program to perform Directory Operations and list files using the dirent.h library.

// Lab 26: Directory Operations and listing files using dirent.h

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>     // opendir(), readdir(), closedir()
#include <sys/stat.h>   // mkdir()
#include <unistd.h>     // rmdir(), getcwd(), chdir()

#define SIZE 256

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Create a directory: mkdir(path, permissions)
void createDir() {
    char name[SIZE];
    printf("Enter directory name to create: ");
    scanf("%255s", name);
    clearBuffer();

    if (mkdir(name, 0755) == 0)
        printf("Directory '%s' created.\n", name);
    else
        perror("mkdir failed");
}

// Remove an EMPTY directory
void removeDir() {
    char name[SIZE];
    printf("Enter directory name to remove: ");
    scanf("%255s", name);
    clearBuffer();

    if (rmdir(name) == 0)
        printf("Directory '%s' removed.\n", name);
    else
        perror("rmdir failed");
}

// List files: opendir -> readdir loop -> closedir
void listDir() {
    char name[SIZE];
    printf("Enter directory to list (. for current): ");
    scanf("%255s", name);
    clearBuffer();

    DIR *dp = opendir(name);
    if (dp == NULL) {
        perror("opendir failed");
        return;
    }

    struct dirent *entry;
    printf("\n--- Contents of %s ---\n", name);
    while ((entry = readdir(dp)) != NULL) {
        char type = '?';
        if (entry->d_type == DT_DIR)      type = 'D';
        else if (entry->d_type == DT_REG) type = 'F';
        printf("[%c] %s\n", type, entry->d_name);
    }
    closedir(dp);
}

// Show current working directory
void showCwd() {
    char path[SIZE];
    if (getcwd(path, SIZE) != NULL)
        printf("Current directory: %s\n", path);
    else
        perror("getcwd failed");
}

// Change current working directory
void changeDir() {
    char name[SIZE];
    printf("Enter directory to move into: ");
    scanf("%255s", name);
    clearBuffer();

    if (chdir(name) == 0)
        printf("Changed directory.\n");
    else
        perror("chdir failed");
}

int main() {
    int choice;
    while (1) {
        printf("\n--- Directory Operations ---\n");
        printf("1. Create directory\n2. Remove directory\n3. List files\n");
        printf("4. Show current directory\n5. Change directory\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearBuffer();

        switch (choice) {
            case 1: createDir(); break;
            case 2: removeDir(); break;
            case 3: listDir();   break;
            case 4: showCwd();   break;
            case 5: changeDir(); break;
            case 6: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}