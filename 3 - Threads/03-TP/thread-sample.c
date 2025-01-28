#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<sys/time.h>
#define SIZE (int)1e8

int tab[SIZE];

const int NUM_THREADS = 1024;

int min = 1000, max = 0;
pthread_mutex_t min_max_mutex;

typedef struct {
    int start;
    int end;
} thread_data;

void init_array() {
    for (int i = 0; i < SIZE; i++) {
        tab[i] = rand() % 1000;
    }
}

void find_min_max(int *min, int *max) {
    *min = tab[0];
    *max = tab[0];
    for (int i = 1; i < SIZE; i++) {
        if (tab[i] < *min) {
            *min = tab[i];
        }
        if (tab[i] > *max) {
            *max = tab[i];
        }
    }
}


void *find_min_max_thread(void *arg) {
    thread_data *data = (thread_data *) arg;
    int local_min = 1000, local_max = 0;
    for (int i = data->start; i < data->end; i++) {
        if (tab[i] < local_min) {
            local_min = tab[i];
        }
        if (tab[i] > local_max) {
            local_max = tab[i];
        }
    }

    pthread_mutex_lock(&min_max_mutex);
    if (local_min < min) min = local_min;
    if (local_max > max) max = local_max;
    pthread_mutex_unlock(&min_max_mutex);

    pthread_exit(NULL);
}

int main() {
    struct timeval start, end;
    int min_sequential, max_sequential;

    init_array();

    gettimeofday(&start, NULL);
    find_min_max(&min_sequential, &max_sequential);
    gettimeofday(&end, NULL);

    printf("Test séquentiel:\n");
    printf("Minimum: %d, Maximum: %d\n", min_sequential, max_sequential);
    printf("Temps d'exécution (séquentiel) : %ld microsecondes\n", 
            (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));

    pthread_t threads[NUM_THREADS];
    thread_data thread_args[NUM_THREADS];
    min = 1000;
    max = 0;
    pthread_mutex_init(&min_max_mutex, NULL);

    gettimeofday(&start, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i].start = i * (SIZE / NUM_THREADS);
        thread_args[i].end = (i + 1) * (SIZE / NUM_THREADS);
        pthread_create(&threads[i], NULL, find_min_max_thread, (void *)&thread_args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    gettimeofday(&end, NULL);

    printf("\nTest avec threads:\n");
    printf("Minimum: %d, Maximum: %d\n", min, max);
    printf("Temps d'exécution (threads) : %ld microsecondes\n", 
            (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));

    pthread_mutex_destroy(&min_max_mutex);

    printf("\n");

    return 0;
}