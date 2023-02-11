#include <pthread.h>
#include <stdio.h>

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
  printf("Thread with start value %d is finished!\n", start);
  return NULL;
}

int main(int argc, char *argv[]) {
  int M;
  printf("Enter the value of M: ");
  scanf("%d", &M);

  int count = 0;
  pthread_t thread1, thread2;
  struct params p1 = {1, M / 2, &count};
  struct params p2 = {M / 2 + 1, M, &count};
  pthread_create(&thread1, NULL, count_primes, &p1);
  pthread_create(&thread2, NULL, count_primes, &p2);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  printf("There are %d prime numbers between 1 and %d\n", count, M);

  return 0;
}

