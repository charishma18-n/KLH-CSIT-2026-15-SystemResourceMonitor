
#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdatomic.h>

#define READERS 4
#define WRITERS 2

static int database = 100;
static pthread_rwlock_t db_lock = PTHREAD_RWLOCK_INITIALIZER;
static atomic_int active_readers = 0;
static atomic_int active_writers = 0;
static atomic_int errors = 0;

typedef struct {
    int id;
} ThreadInfo;

void pause_ms(long ms) {
    struct timespec t = { ms / 1000, (ms % 1000) * 1000000L };
    nanosleep(&t, NULL);
}

void *reader(void *arg) {
    ThreadInfo *info = arg;

    for (int i = 0; i < 3; i++) {
        pthread_rwlock_rdlock(&db_lock);

        atomic_fetch_add(&active_readers, 1);
        if (atomic_load(&active_writers) != 0)
            atomic_fetch_add(&errors, 1);

        printf("Reader %d is reading database value: %d\n",
               info->id, database);
        fflush(stdout);
        pause_ms(300);

        atomic_fetch_sub(&active_readers, 1);
        pthread_rwlock_unlock(&db_lock);
        pause_ms(100);
    }
    return NULL;
}

void *writer(void *arg) {
    ThreadInfo *info = arg;

    for (int i = 0; i < 2; i++) {
        printf("Writer %d requests write access\n", info->id);
        fflush(stdout);

        pthread_rwlock_wrlock(&db_lock);

        atomic_fetch_add(&active_writers, 1);
        if (atomic_load(&active_readers) != 0 ||
            atomic_load(&active_writers) != 1)
            atomic_fetch_add(&errors, 1);

        database += 10;
        printf("Writer %d updated database value to: %d\n",
               info->id, database);
        fflush(stdout);
        pause_ms(400);

        atomic_fetch_sub(&active_writers, 1);
        pthread_rwlock_unlock(&db_lock);
        pause_ms(150);
    }
    return NULL;
}

int main(void) {
    pthread_t r[READERS], w[WRITERS];
    ThreadInfo ri[READERS], wi[WRITERS];

    printf("=== Readers-Writers Concurrent Database Simulator ===\n");
    printf("Initial database value: %d\n\n", database);

    for (int i = 0; i < READERS; i++) {
        ri[i].id = i + 1;
        if (pthread_create(&r[i], NULL, reader, &ri[i]) != 0) {
            perror("Could not create reader thread");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < WRITERS; i++) {
        wi[i].id = i + 1;
        if (pthread_create(&w[i], NULL, writer, &wi[i]) != 0) {
            perror("Could not create writer thread");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < READERS; i++)
        pthread_join(r[i], NULL);

    for (int i = 0; i < WRITERS; i++)
        pthread_join(w[i], NULL);

    printf("\n=== Simulation Results ===\n");
    printf("Initial value: 100\n");
    printf("Final database value: %d\n", database);
    printf("Expected final value: 140\n");
    printf("Synchronization violations: %d\n",
           atomic_load(&errors));
    printf("Status: %s\n",
           atomic_load(&errors) == 0 && database == 140
               ? "PASSED" : "FAILED");

    pthread_rwlock_destroy(&db_lock);
    return atomic_load(&errors) == 0 && database == 140
               ? EXIT_SUCCESS : EXIT_FAILURE;
}

