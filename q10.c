// Lab 10: Write a C program to create multiple threads using the POSIX pthread library.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

typedef struct
{
    int thread_id;
    char* msg;// char* since msg is string not a single char
}ThreadData;

void* print_msg(void* arg){
    ThreadData* data = (ThreadData*)arg;

    printf("\nThread[%d] Started running... | Status: %s",data->thread_id, data->msg );
    
    //pretend to work for 1sec
    sleep(1);
    
    printf("\nThread[%d] Finished running",data->thread_id );

}

int main(){

    pthread_t threads[5]; //array for holding threads of datatype pthreathread_t

    ThreadData thread_data[5]; //instances of struct ThreadData

    int rc; //exit codes returned by pthread fns

    //create threads
    for (int i = 0; i < 5; i++)
    {
        thread_data[i].thread_id = i+1;
        thread_data[i].msg = "Hello from POSIX thread!\0";
        //passing addr of thread_data[i] by typecasting it to void pointer
        //NULL for default thread attributes
        //int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
        rc = pthread_create(&threads[i], NULL, print_msg, (void*)&thread_data[i]); //returns non negative exit code if error else 0

        if (rc) // if rc is non negative
        {
            fprintf(stderr, "\nFailed to create thread[%d] | Returned code: %d\n", i+1, rc);
            exit(EXIT_FAILURE);
        }
        
    }

    //wait for child threads to finish running before main exits cuz 
    // in c everything runs from main and any other threads running is killed once main exits
    for (int i = 0; i < 5; i++)
    {
        // int pthread_join(pthread_t thread, void **retval);
        rc = pthread_join(threads[i], NULL);
        if (rc) // if rc is non negative
        {
            fprintf(stderr, "\nFailed to join thread[%d] | Returned code: %d\n", i+1, rc);
            exit(EXIT_FAILURE);
        }
    }

    printf("\nMain thread: All threads completed successfully. Exiting.\n");    

    return 0;
}


