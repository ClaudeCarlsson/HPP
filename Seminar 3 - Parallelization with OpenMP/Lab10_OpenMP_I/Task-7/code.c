#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif

int is_prime(int n)
{
  if (n <= 1)
  {
    return 0;
  }
  int limit = (int)sqrt(n);
  for (int i = 2; i <= limit; i++)
  {
    if (n % i == 0)
    {
      return 0;
    }
  }
  return 1;
}

int count_primes(int M, int num_threads)
{
  int count = 0;
  int i;
#pragma omp parallel for num_threads(num_threads) schedule(dynamic, num_threads) reduction(+ \
                                                                                           : count)
  for (i = 0; i < M; i++)
  {
    // check if i is prime
    if (is_prime(i))
    {
      // increment the count
      count++;
    }
  }
  return count;
}

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    fprintf(stderr, "Usage: %s <M> <num_threads>\n", argv[0]);
    return 1;
  }
  int M = atoi(argv[1]);
  int num_threads = atoi(argv[2]);
  double t1 = 0, t2 = 0;
#ifdef _OPENMP
  t1 = omp_get_wtime();
#endif
  int count = count_primes(M, num_threads);
#ifdef _OPENMP
  t2 = omp_get_wtime();
#endif

  printf("Found %d prime numbers between 0 and %d\n", count, M);
  printf("Time taken: %f seconds\n", t2 - t1);

  return 0;
}