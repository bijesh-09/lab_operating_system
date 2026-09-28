// Lab 15: Implement First Fit, Best Fit, and Worst Fit Memory Allocation Algorithms.

#include<stdio.h>
#include <string.h> //for memcpy()
#define MAX 20

void firstFit(int blocks[MAX], int m, int procs[MAX], int n){
    int alloc[n], b[MAX];
    //b as copy of blocks cuz modifying blocks would affect other bestfit and worstfit fns
    
    // void *memcpy(void *dest, const void *src, size_t n); n is no. of bytes
    memcpy(b, blocks, sizeof(int)*m);

    for(int i = 0; i < n; i++) alloc[i] = -1; //-1 means mem is not allocated yet for ith process

    //find fitting block for each process
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (b[j] >= procs[i]) //find first fitting block for ith process's size
            {
                alloc[i] = j; //allocated jth block for ith process
                b[j] -= procs[i]; //update block size to its remaining size 
                break;
            }
            
        }
        
    }

    printf("\n--- First Fit ---\n");
    printf("Process\tSize\tBlock\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t", i+1, procs[i]);
        if (alloc[i] != -1) printf("%d\n",alloc[i] + 1); //allocated block no.
        else printf("Not Allocated!\n");
    }
    
}

void bestFit(int blocks[MAX], int m, int procs[MAX], int n){
    int alloc[n], b[MAX];
    memcpy(b, blocks, sizeof(int)*m);
    for(int i = 0; i < n; i++) alloc[i] = -1;

    //find smallest block big enough to hold process
    for (int i = 0; i < n; i++)
    {
        int best = -1; //best jth block for ith process, -1 means best block not found 
        for (int j = 0; j < m; j++)
        {
            if (b[j] >= procs[i]) //find fitting block for ith process's size
            {
                if (best == -1 || b[j] < b[best]) 
                {
                    //if smaller block found than curr best block then update best block to it
                    best = j;
                }
                
            }
            
        }
        if (best != -1)
        {
            alloc[i] = best; //allocated best jth block for ith process
            b[best] -= procs[i]; //update best block size to its remaining size
        }
        
        
    }
    
    printf("\n--- Best Fit ---\n");
    printf("Process\tSize\tBlock\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t", i+1, procs[i]);
        if (alloc[i] != -1) printf("%d\n",alloc[i] + 1); //allocated block no.
        else printf("Not Allocated!\n");
    }
    
}
void worstFit(int blocks[MAX], int m, int procs[MAX], int n)
{
    int alloc[n], b[MAX];
    memcpy(b, blocks, sizeof(int)*m);
    for(int i = 0; i < n; i++) alloc[i] = -1;

    
    //find biggest block available to hold process
    for (int i = 0; i < n; i++)
    {
        int worst = -1; //worst jth block for ith process, -1 means worst block not found 
        for (int j = 0; j < m; j++)
        {
            if (b[j] >= procs[i]) //find fitting block for ith process's size
            {
                if (worst == -1 || b[j] > b[worst]) 
                {
                    //if bigger block found than curr worst block then update worst block to it
                    worst = j;
                }
                
            }
            
        }
        if (worst != -1)
        {
            alloc[i] = worst; //allocated best jth block for ith process
            b[worst] -= procs[i]; //update best block size to its remaining size
        }
        
        
    }

    printf("\n--- Worst Fit ---\n");
    printf("Process\tSize\tBlock\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t", i+1, procs[i]);
        if (alloc[i] != -1) printf("%d\n",alloc[i] + 1); //allocated block no.
        else printf("Not Allocated!\n");
    }
}

int main(){
    int blocks[MAX], procs[MAX];
    int m, n;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter sizes of blocks:\n");
    for (int i = 0; i < m; i++) scanf("%d", &blocks[i]);

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter sizes of processes:\n");
    for (int i = 0; i < n; i++) scanf("%d", &procs[i]);

    firstFit(blocks, m, procs, n);
    bestFit(blocks, m, procs, n);
    worstFit(blocks, m, procs, n);
    return 0;
}