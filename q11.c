// Lab 11: Implement the Producer-Consumer Problem using threads and synchronization techniques.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define N 5              // Number of slots in buffer
#define NUM_PRODUCERS 2  // Number of producer threads
#define NUM_CONSUMERS 2  // Number of consumer threads

int buffer[N]; //will be used as queue FIFO
int in = 0;
int out = 0;

sem_t mutex;
sem_t empty;
sem_t full;

// Helper functions
int produce_item() {
    int item = rand() % 100 + 1; // Produce a random integer between 1 and 100
    return item;
}

int insert_item(int item){
    buffer[in] = item;
    printf("[PRODUCER] Inserted item %d at buffer[%d]\n", item, in);
    in = (in + 1) % N;
}

int remove_item() {
    int item = buffer[out];
    printf("-->[CONSUMER] Removed item %d from buffer[%d]\n", item, out);
    out = (out + 1) % N;
    return item;
}

void consume_item(int item) {
    printf("-->[CONSUMER] Consumed item %d\n", item);
}

//producer and consumer fns
void* producer(void* arg){
    int id = *(int*)arg; //poitner typecasting and then dereferencing

    for (int cycles = 0; cycles < N; cycles++)
    {
        sem_wait(&empty); //equivalent to down()
        sem_wait(&mutex);
        printf("Producer[%d] in Critical Region\n", id);
        insert_item(produce_item()); // "in" increments in buffer (cricular queue)
        sem_post(&mutex);// equivalent to up()
        sem_post(&full);
    }
    
    //pretend producer is doing other works as well
    sleep(1);

}
void* consumer(void* arg){
    int id = *(int*)arg; //poitner typecasting and then dereferencing
    
    for (int cycles = 0; cycles < N; cycles++)
    {
        sem_wait(&full); //equivalent to down()
        sem_wait(&mutex);
        printf("Consumer[%d] in Critical Region\n", id);
        consume_item(remove_item());
        sem_post(&mutex);// equivalent to up()
        sem_post(&empty);
    }
    
    //pretend consumer is doing other works as well
    sleep(2);

}

int main(){

    // int sem_init(sem_t *sem, int pshared, unsigned int value);
    //pshared = 0 means all threads of this process(this program) share the semaphore
    sem_init(&mutex, 0, 1); //init mutex to 1
    sem_init(&empty, 0, N); //init empty to N
    sem_init(&full, 0, 0); //init empty to 0

    int rc; // return code of pthread fns

    //threads for each 2 producers and 2 consumers
    pthread_t prod_threads[NUM_PRODUCERS]; 
    pthread_t cons_threads[NUM_CONSUMERS]; 
    int prod_thread_id[NUM_PRODUCERS];
    int cons_thread_id[NUM_CONSUMERS];

    //create producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        prod_thread_id[i] = i+1;
        
        //passing addr of thread_data[i] by typecasting it to void pointer
        //NULL for default thread attributes
        //int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
        rc = pthread_create(&prod_threads[i], NULL, producer, (void*)&prod_thread_id[i]);    
        
        if (rc) // if rc is non negative
        {
            fprintf(stderr, "\nFailed to create producer_thread[%d] | Returned code: %d\n", i+1, rc);
            exit(EXIT_FAILURE);
        }
        
    }
    //create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        cons_thread_id[i] = i+1;

        rc = pthread_create(&cons_threads[i], NULL, consumer, (void*)&cons_thread_id[i]);    

        if (rc) // if rc is non negative
        {
            fprintf(stderr, "\nFailed to create consumer_thread[%d] | Returned code: %d\n", i+1, rc);
            exit(EXIT_FAILURE);
        }

    }

    //wait for threads to finish running before main exits

    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        // int pthread_join(pthread_t thread, void **retval);
        rc = pthread_join(prod_threads[i], NULL);
        if (rc) // if rc is non negative
        {
            fprintf(stderr, "\nFailed to join producer_thread[%d] | Returned code: %d\n", i, rc);
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        // int pthread_join(pthread_t thread, void **retval);
        rc = pthread_join(cons_threads[i], NULL);
        if (rc) // if rc is non negative
        {
            fprintf(stderr, "\nFailed to join consumer_thread[%d] | Returned code: %d\n", i, rc);
            exit(EXIT_FAILURE);
        }
    }

    //destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    printf("\nMain thread: All producer and consumer threads finished successfully.\n");

    return 0;
}

