#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv)
{
  omp_set_num_threads(6);
#pragma omp parallel

  {
    printf("Bonjour!\n");
  }

  return 0;
}
