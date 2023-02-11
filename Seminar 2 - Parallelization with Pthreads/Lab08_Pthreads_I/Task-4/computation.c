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


int main(int argc, char *argv[]) {
  int M;
  printf("Enter the value of M: ");
  scanf("%d", &M);

  int count = 0;
  for (int i = 1; i <= M; i++) {
    if (is_prime(i)) {
      count++;
    }
  }

  printf("There are %d prime numbers between 1 and %d\n", count, M);

  return 0;
}




