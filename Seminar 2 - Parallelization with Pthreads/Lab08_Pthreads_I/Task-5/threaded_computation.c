#include <pthread.h>
#include <stdio.h>

struct params {
  int thread_id;
};

void *print_thread_id(void *arg) {
  struct params *p = (struct params *)arg;
  int thread_id = p->thread_id;

  printf("This is thread %d\n", thread_id);

  return NULL;
}

int main(int argc, char *argv[]) {
  int N;
  printf("Enter the number of threads: ");
  scanf("%d", &N);

  pthread_t threads[N];
  for (int i = 0; i < N; i++) {
    struct params p = {i};
    pthread_create(&threads[i], NULL, print_thread_id, &p);
    pthread_join(threads[i], NULL);
  }

  return 0;
}