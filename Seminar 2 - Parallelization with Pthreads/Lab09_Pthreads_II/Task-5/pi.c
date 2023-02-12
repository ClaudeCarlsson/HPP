#include <stdio.h>
#include <pthread.h>

pthread_mutex_t m;
double global_pi_result = 0;

struct params
{
  double dx;
  long int lower_bound, upper_bound;
};

double calc_pi(struct params p) {
  double dx = p.dx;
  long int lower_bound = p.lower_bound;
  long int upper_bound = p.upper_bound;

  double sum = 0;

  for (long int i = lower_bound; i < upper_bound; i++) {
    double x = dx * (i + 0.5);
    sum += dx * 4.0 / (1.0 + x * x);
  }
  return sum;
}

void *thread_func(void *arg) {
  struct params *p = (struct params *)arg;
  double thread_sum = calc_pi(*p);

  pthread_mutex_lock(&m);
  global_pi_result += thread_sum;
  pthread_mutex_unlock(&m);

  return NULL;
}

int main() {
  int M;
  printf("Please enter the amount of threads: ");
  if (scanf("%d", &M) != 1) {
    printf("Invalid input. Please enter an integer.\n");
    return 1;
  }
  pthread_t threads[M];
  struct params p[M];
  pthread_mutex_init(&m, NULL);

  const long int data_points = 500000000;
  const long int interval_points = data_points / M;
  const double dx = 1.0 / data_points;

  for (int i = 0; i < M; i++) {
    p[i].dx = dx;
    p[i].lower_bound = i * interval_points;
    p[i].upper_bound = (i + 1) * interval_points;

    if (i == M - 1) {
      p[i].upper_bound = data_points;
    }

    printf("%9.ld -- %ld \n" , p[i].lower_bound, p[i].upper_bound);
    pthread_create(&threads[i], NULL, thread_func, &p[i]);
  }

  for (int i = 0; i < M; i++) {
    pthread_join(threads[i], NULL);
  }

  double pi = 3.1415926535897932384626433832795028L;
  printf("PI is approximate: %.16f with %d threads.\n", global_pi_result, M);
  printf("Difference: %e\n", (global_pi_result - pi));

  pthread_mutex_destroy(&m);

  return 0;
}