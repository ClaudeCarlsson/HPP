#include <stdio.h>
#include <time.h>
#include <math.h>

inline int add(int a, int b) {
  double result = sin(a) * cos(b) * sqrt(a) * sqrt(b) * sin(a) * cos(b) * sqrt(a) * sqrt(b);
  return (int)result;
}

int main() {
  int i, sum = 0;
  clock_t start, end;

  start = clock();
  for (i = 0; i < 100000000; i++) {
    if (i%2 == 0) {
      sum += add(i, i + 1);
    } else {
      sum *= add(i, i + 1);
    }
    
  }
  end = clock();

  printf("Time taken to execute function add(): %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

  return 0;
}