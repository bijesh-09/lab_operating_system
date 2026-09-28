// Lab 27: Display and modify File Permissions using chmod()

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>   // stat(), chmod(), permission macros

#define SIZE 256

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Print permissions like ls -l does, e.g. rw-r--r--
void printPermissions(mode_t mode) {
    printf("%c%c%c", (mode & S_IRUSR) ? 'r' : '-',
                     (mode & S_IWUSR) ? 'w' : '-',
                     (mode & S_IXUSR) ? 'x' : '-');
    printf("%c%c%c", (mode & S_IRGRP) ? 'r' : '-',
                     (mode & S_IWGRP) ? 'w' : '-',
                     (mode & S_IXGRP) ? 'x' : '-');
    printf("%c%c%c", (mode & S_IROTH) ? 'r' : '-',
                     (mode & S_IWOTH) ? 'w' : '-',
                     (mode & S_IXOTH) ? 'x' : '-');
}

// Display: stat() fills a struct with the file's inode info
void displayPermissions() {
    char name[SIZE];
    struct stat st;

    printf("Enter file name: ");
    scanf("%255s", name);
    clearBuffer();

    if (stat(name, &st) == -1) {
        perror("stat failed");
        return;
    }

    printf("Permissions of '%s': ", name);
    printPermissions(st.st_mode);
    printf("  (octal %o)\n", st.st_mode & 0777);
}

// Modify: chmod(path, mode)
void modifyPermissions() {
    char name[SIZE];
    int mode;

    printf("Enter file name: ");
    scanf("%255s", name);
    printf("Enter new permissions in octal (e.g. 644, 755): ");
    scanf("%o", &mode);   // %o reads the number as octal
    clearBuffer();

    if (chmod(name, mode) == 0) {
        printf("Permissions changed to %o.\n", mode);
    } else {
        perror("chmod failed");
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n--- File Permissions ---\n");
        printf("1. Display permissions\n2. Modify permissions\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearBuffer();

        switch (choice) {
            case 1: displayPermissions(); break;
            case 2: modifyPermissions();  break;
            case 3: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}