
// Lab 12: Implement the Reader-Writer Problem using semaphores.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_READERS 3  // Number of reader threads
#define NUM_WRITERS 2  // Number of writer threads

// Shared resource and tracking variables
int shared_data = 100; // The resource being read/written
int read_count = 0;    // Number of readers currently reading

// Semaphores
sem_t rw_mutex; // Binary semaphore: controls exclusive access for writers (and 1st/last reader)
sem_t mutex;    // Binary semaphore: protects updates to read_count variable

// Reader routine
void* reader(void* arg) {
    int id = *(int*)arg;

    for (int cycles = 0; cycles < 3; cycles++) {
        // --- Entry Section for Reader ---
        sem_wait(&mutex); // Lock read_count
        read_count++;
        if (read_count == 1) {
            // First reader locks the resource so no writer can enter
            sem_wait(&rw_mutex); 
        }
        sem_post(&mutex); // Unlock read_count

        // --- Critical Region (Reading) ---
        printf("[READER %d] Reading shared_data = %d (Active readers: %d)\n", id, shared_data, read_count);
        sleep(1); // Pretend reading takes some time

        // --- Exit Section for Reader ---
        sem_wait(&mutex); // Lock read_count
        read_count--;
        if (read_count == 0) {
            // Last reader releases the resource so writers can enter
            sem_post(&rw_mutex); 
        }
        sem_post(&mutex); // Unlock read_count

        sleep(2); // Pretend reader is doing other work outside
    }

    return NULL;
}

// Writer routine
void* writer(void* arg) {
    int id = *(int*)arg;

    for (int cycles = 0; cycles < 3; cycles++) {
        // --- Entry Section for Writer ---
        sem_wait(&rw_mutex); // Lock the resource (exclusive access)

        // --- Critical Region (Writing) ---
        int new_value = rand() % 1000 + 1;
        shared_data = new_value;
        printf("-->[WRITER %d] Updated shared_data to %d\n", id, shared_data);
        sleep(2); // Pretend writing takes some time

        // --- Exit Section for Writer ---
        sem_post(&rw_mutex); // Release the resource

        sleep(3); // Pretend writer is doing other work outside
    }

    return NULL;
}

int main() {
    int rc;

    // Initialize semaphores
    // rw_mutex = 1 (Controls writing access & first/last reader entry)
    // mutex    = 1 (Protects read_count variable)
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);

    pthread_t reader_threads[NUM_READERS];
    pthread_t writer_threads[NUM_WRITERS];

    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    // Create Reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        rc = pthread_create(&reader_threads[i], NULL, reader, (void*)&reader_ids[i]);
        if (rc) {
            fprintf(stderr, "Failed to create reader_thread[%d] | Code: %d\n", i + 1, rc);
            exit(EXIT_FAILURE);
        }
    }

    // Create Writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        rc = pthread_create(&writer_threads[i], NULL, writer, (void*)&writer_ids[i]);
        if (rc) {
            fprintf(stderr, "Failed to create writer_thread[%d] | Code: %d\n", i + 1, rc);
            exit(EXIT_FAILURE);
        }
    }

    // Join Reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        rc = pthread_join(reader_threads[i], NULL);
        if (rc) {
            fprintf(stderr, "Failed to join reader_thread[%d] | Code: %d\n", i + 1, rc);
            exit(EXIT_FAILURE);
        }
    }

    // Join Writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        rc = pthread_join(writer_threads[i], NULL);
        if (rc) {
            fprintf(stderr, "Failed to join writer_thread[%d] | Code: %d\n", i + 1, rc);
            exit(EXIT_FAILURE);
        }
    }

    // Destroy semaphores
    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    printf("\nMain thread: All reader and writer threads finished successfully.\n");

    return 0;
}