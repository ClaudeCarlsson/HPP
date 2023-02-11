#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2

void *worker(void *arg) {
    int id = *(int*) arg;
    printf("Thread %d starting\n", id);
    pthread_t threads[NUM_THREADS];
    int i;
    for (i = 0; i < NUM_THREADS; i++) {
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&threads[i], NULL, worker, arg);
    }
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        free(arg);
    }
    printf("Thread %d finishing\n", id);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    printf("Main thread starting\n");
    pthread_t threads[NUM_THREADS];
    int i;
    for (i = 0; i < NUM_THREADS; i++) {
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&threads[i], NULL, worker, arg);
    }
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Main thread finishing\n");
    return 0;
}