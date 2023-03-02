#include <stdio.h>
#include <omp.h>

void thread_func()
{
  int id = omp_get_thread_num();
  int num_threads = omp_get_num_threads();
  printf("This is inside thread_func() with thread ID %d out of %d threads\n", id, num_threads);
}

int main(int argc, char **argv)
{

#pragma omp parallel num_threads(2)
  {
    thread_func();
  }

  return 0;
}