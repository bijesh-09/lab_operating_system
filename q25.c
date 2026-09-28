// Lab 25: Write a C program to perform basic File Operations
//  (Create, Read, Write, Append, and Copy Files).

#include<stdio.h>
#define SIZE 256

// clears leftover input (like the '\n' after scanf) so fgets works properly
void clearBuffer(){
    int c;
    //getchar() returns the asci code of a char
    while((c = getchar()) != '\n' && c != EOF); //getchar works is fgetc(stdin) in disguise
}

// Create + Write: "w" creates the file, or erases it if it already exists
void createWrite(){
    char name[50], text[SIZE];
    printf("Enter filename: ");
    scanf("%49s", name); //read at most 49 chars cuz last byte needed for null terminator, and name is declared 50 bytes array declared
    clearBuffer(); //clean the leftover '\n' after scanf cuz scanf leaves '\n' behind 
    
    FILE* fp = fopen(name, "w");
    if (fp == NULL)
    {
        printf("Error: could not create file\n");
        return;
    }
    
    printf("Enter text for file: ");
    
    // char *fgets(char *buf, int size, FILE *fp);   // read a line and return buf or NULL on error/eof
    fgets(text, SIZE, stdin); //stdin is also a file pointer pointing to keyboard
    
    // int   fputs(const char *str, FILE *fp);       // write a string, returns non-negative on success, EOF on error
    fputs(text, fp); //the text has become buf pointer returned by fgets to text[] array
    
    fclose(fp); // closes the file and flushes data in ram to file in disk
    
    printf("File written successfully.\n");
}

void readFile(){
    char name[50], text[SIZE];
    int ch; //cuz fgetc returns char as int(ASCII code)
    printf("Enter filename: ");
    scanf("%49s", name);
    
    FILE* fp = fopen(name, "r");
    if (fp == NULL)
    {
        printf("Error: file does not exist\n");
        return;
    }
    printf("\n--- Contents of %s ---\n", name);
    // int   fgetc(FILE *fp); // read one character, returns the char as an int, or EOF (-1)
    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(ch); //displays int ch as char in stdout 
    }
    fclose(fp);
}

void appendFile(){
    
    char name[50], text[SIZE];
    printf("Enter filename: ");
    scanf("%49s", name);
    clearBuffer();
    
    FILE* fp = fopen(name, "a");
    if (fp == NULL)
    {
        printf("Error: file does not exist\n");
        return;
    }
    printf("Enter text to append for file: ");
    fgets(text, SIZE, stdin); //read stdin
    fputs(text, fp);
    fclose(fp);
    printf("Text appended successfully.\n");
}

void copyFile(){
    char src[50], dest[50];
    int ch;
    printf("Enter source filename: ");
    scanf("%49s", src);

    printf("Enter destination filename: ");
    scanf("%49s", dest);
    clearBuffer();

    FILE* fs = fopen(src, "r");
    if (fs == NULL)
    {
        printf("Error: Source file does not exist\n");
        return;
    }
    FILE* fd = fopen(dest, "a");
    if (fd == NULL)
    {
        printf("Error: could not create destn file\n");
        return;
    }
    while ((ch = fgetc(fs)) != EOF)
    {
        // int   fputc(int ch, FILE *fp); // write one character, returns the char written, or EOF on error
        fputc(ch, fd);
    }
    fclose(fs);
    fclose(fd);
    printf("File copied successfully.\n");
}

int main() {
    int choice;
    while (1) {
        printf("\n--- File Operations ---\n");
        printf("1. Create & Write\n2. Read\n3. Append\n4. Copy\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearBuffer();

        switch (choice) {
            case 1: createWrite(); break;
            case 2: readFile();    break;
            case 3: appendFile();  break;
            case 4: copyFile();    break;
            case 5: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}