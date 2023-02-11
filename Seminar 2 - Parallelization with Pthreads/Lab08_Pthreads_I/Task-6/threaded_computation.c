#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_prime(int num) {
  if (num <= 1) {
    return 0;
  }

  for (int i = 2; i < num; i++) {
    if (num % i == 0) {
      return 0;
    }
  }

  return 1;
}

struct params {
  int start;
  int end;
  int *count;
};

void *count_primes(void *arg) {
  struct params *p = (struct params *)arg;
  int start = p->start;
  int end = p->end;
  int *count = p->count;

  for (int i = start; i <= end; i++) {
    if (is_prime(i)) {
      (*count)++;
    }
  }

  return NULL;
}

int main(int argc, char *argv[]) {
  int M, N;
  printf("Enter the value of M: ");
  scanf("%d", &M);
  printf("Enter the number of threads: ");
  scanf("%d", &N);

  int count = 0;
  int range = ceil((double)M / N);
  pthread_t threads[N];
  struct params p[N];
  for (int i = 0; i < N; i++) {
    p[i].start = (i * range + 1);
    p[i].end = fmin((i + 1) * range, M);
    p[i].count = &count;
    pthread_create(&threads[i], NULL, count_primes, &p[i]);
  }

  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], NULL);
  }

  printf("There are %d prime numbers between 1 and %d\n", count, M);

  return 0;
}