// Lab 13: Implement the Dining Philosophers Problem using synchronization techniques.

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

#define N 5 //5 philosophers
#define LEFT (i+N-1)%N //current philosopher's left side person
#define RIGHT (i+1)%N //current philosopher's right side person
#define HUNGRY 0
#define THINKING 1
#define EATING 2

sem_t mutex; //shared binary semaphore for handling takeforks or putforks
sem_t S[N]; //binary semaphore for each phil, phil goes to sleep if they dont get EATING on takeforks

int state[N]; // phil's current state: THINKING or HUNGRY or EATING

int phil[N] = {0, 1, 2, 3, 4};//initing the philosophers

void test(int i){
    //neither of the immediate neighbors of current phil should be EATING
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        state[i] = EATING;

        sem_post(&S[i]); // equivalent to up(&S[i])
    }
    
}

void take_forks(int i){
    sem_wait(&mutex);
    state[i] = HUNGRY; // since curr phil gonna take forks but may or may not get forks
    printf("\nPhilosopher[%d] is HUNGRY | Trying to take forks\n", i + 1);
    test(i);
    sem_post(&mutex);
    
    sem_wait(&S[i]); // remains as it was (i.e. 0) if ith phil got forks , otherwise phil goes to sleep
    printf("Philosopher[%d] is EATING\n", i + 1);
}

void put_forks(int i){
    sem_wait(&mutex);
    state[i] = THINKING; //since phil is done eating now it goes to thinking
    printf("\nPhilosopher[%d] puts down forks and starts THINKING\n", i + 1);
    test(LEFT);// give chance to left phil if he is hungry
    test(RIGHT);// give chance to right phil if he is hungry or (left didnt get the forks cuz either left is THINKING or left's one of the immediate neighbors is EATING)
    sem_post(&mutex);
}

void* philosopher(void* pos){
    int i = *(int*)pos; // pointcast the void pointer pos into int, and dereference it to get the value pointed by pos
    
    sleep(THINKING); // pretend philosopher is THINKING, sleeps 1 sec
    take_forks(i);
    sleep(EATING); // pretend philosopher is EATING, sleeps 2 secs
    put_forks(i);
    printf("---------------------------------------------------\n");

}

int main(){

    // init semaphores
    // int sem_init(sem_t *sem, int pshared, unsigned int value);
    //pshared = 0 means all threads of this process(this program) share the semaphore
    //value means initial value of semaphore
    sem_init(&mutex, 0, 1); // init mutex to 1

    for (int i = 0; i < N; i++)
    {
        //if phil get to Eating S[i] ups to 1 in test() and then downs to 0 in takeforks() 
        //if phil doesnt get to Eating S[i] remains 0 as it is and then sleeps(down 0) in takeforks() 
        sem_init(&S[i], 0, 0); // init S[i] to 0
    }

    int rc; // return code of pthread fns

    pthread_t thread_id[N]; //create thread id
    //create threads for each phil
    for (int i = 0; i < N; i++)
    {
        //passing addr of thread_data[i] by typecasting it to void pointer
        //NULL for default thread attributes
        //int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
        rc = pthread_create(&thread_id[i], NULL, philosopher, (void*)&phil[i]);    

        if (rc) // if rc is non negative
        {
            fprintf(stderr, "\nFailed to create thread[%d] for phil[%d] | Returned code: %d\n", i, i+1, rc);
            exit(EXIT_FAILURE);
        }

         printf("Philosopher[%d] is THINKING\n", i + 1);
    }
    
    //wait for child threads to finish running before main exits
    for (int i = 0; i < 5; i++)
    {
        // int pthread_join(pthread_t thread, void **retval);
        rc = pthread_join(thread_id[i], NULL);
        if (rc) // if rc is non negative
        {
            fprintf(stderr, "\nFailed to join thread[%d] | Returned code: %d\n", i, rc);
            exit(EXIT_FAILURE);
        }
    }

    //destroy semaphores
    sem_destroy(&mutex);
    for (int i = 0; i < N; i++)
    {
        sem_destroy(&S[i]);
    }
    

    printf("\nMain thread: All threads completed successfully. Exiting.\n");
    

    return 0;
}