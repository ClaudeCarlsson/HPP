#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int N = 100000;

struct params {
  long int *sum;
  pthread_mutex_t *mutex;
};

void* the_thread_func(void* arg) {
  struct params *p = (struct params *)arg;
  long int *sum = p->sum;
  pthread_mutex_t *mutex = p->mutex;
  for(int i = 1; i <= N; ++i) {
    pthread_mutex_lock(mutex);
  	(*sum)++;
    pthread_mutex_unlock(mutex);
  }

  return NULL;
}

int main(int argc, char **argv) {

  if(argc != 2) {printf("Usage: %s N\n", argv[0]); return -1; }

  printf("This is the main() function starting.\n");

  int N = atoi(argv[1]);

  /* Start thread. */
  printf("the main() function now calling pthread_create().\n");
  pthread_t threads[N];
  struct params p[N];
  long int sum = 0;
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  for(int i = 0; i < N; i++) {
    p[i].sum = &sum;
    p[i].mutex = &mutex;
    pthread_create(&threads[i], NULL, the_thread_func, &p[i]);
  }

  printf("This is the main() function after pthread_create()\n");


  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join().\n");
  for(int i = 0; i < N; i++)
    pthread_join(threads[i], NULL);

  printf("sum = %ld\n", sum); 
  
  /* Clean up the mutex. */
  pthread_mutex_destroy(&mutex);

  return 0;
}