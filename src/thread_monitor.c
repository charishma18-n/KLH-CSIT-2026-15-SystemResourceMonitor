#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "thread_monitor.h"

int shared_counter = 0;

pthread_mutex_t counter_mutex;
sem_t start_semaphore;

void *cpu_thread(void *arg)
{
	(void)arg;
    pthread_mutex_lock(&counter_mutex);

    shared_counter++;

    printf("\nCPU Monitoring Thread started.");
    printf("\nCPU Thread updated shared counter: %d\n",
           shared_counter);

    pthread_mutex_unlock(&counter_mutex);

    sem_post(&start_semaphore);

    return NULL;
}

void *memory_thread(void *arg)
{
    (void)arg;
	sem_wait(&start_semaphore);

    pthread_mutex_lock(&counter_mutex);

    shared_counter++;

    printf("Memory Monitoring Thread started.");
    printf("\nMemory Thread updated shared counter: %d\n",
           shared_counter);

    pthread_mutex_unlock(&counter_mutex);

    return NULL;
}

void show_thread_monitor()
{
    pthread_t thread1;
    pthread_t thread2;

    shared_counter = 0;

    pthread_mutex_init(&counter_mutex, NULL);
    sem_init(&start_semaphore, 0, 0);

    printf("\n========================================\n");
    printf("      THREAD & SYNCHRONIZATION\n");
    printf("========================================\n");

    pthread_create(&thread1, NULL, cpu_thread, NULL);
    pthread_create(&thread2, NULL, memory_thread, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("\nBoth monitoring threads completed.");
    printf("\nFinal shared counter: %d\n", shared_counter);

    sem_destroy(&start_semaphore);
    pthread_mutex_destroy(&counter_mutex);

    printf("========================================\n");
}
