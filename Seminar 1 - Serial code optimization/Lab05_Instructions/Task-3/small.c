#include <stdio.h>
#include <math.h>
#include <float.h>

int main(void) {
  float x = 1.0f;
  
  for (int i = 0; i < 100; i++) {
    x *= 100.0f;
    printf("x = %e\n", x);
    if (x == INFINITY) {
      printf("x became INF at iteration %d\n", i);
      break;
    }
  }
  
  printf("Testing NaN:\n");
  x = sqrt(-1.0f);
  if (isnan(x)) {
    printf("sqrt(-1.0f) = NaN\n");
  }
  
  printf("Testing operations on NaN:\n");
  float y = x + 1.0f;
  if (isnan(y)) {
    printf("NaN + 1.0f = NaN\n");
  }
  
  printf("Testing operations on INF:\n");
  x = INFINITY;
  y = x + 1.0f;
  printf("INF + 1.0f = %e\n", y);
  
  return 0;
}