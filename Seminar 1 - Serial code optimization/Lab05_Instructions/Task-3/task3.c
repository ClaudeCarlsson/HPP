#include <stdio.h>

int main() {
   float epsilon = 1.0f;
   float result;
   int count = 0;
   
   while (epsilon + 1.0f > 1.0f) {
      result = epsilon + 1.0f;
      epsilon *= 0.5f;
      count++;
   }
   
   printf("The smallest representable value of epsilon is %e\n", epsilon);
   printf("The result of adding epsilon to 1 became exactly 1 after %d iterations\n", count);


   double depsilon = 1.0;
   double dresult;
   count = 0;
   
   while (depsilon + 1.0 > 1.0) {
      dresult = depsilon + 1.0;
      depsilon *= 0.5;
      count++;
   }
   
   printf("The smallest representable value of epsilon is %e\n", depsilon);
   printf("The result of adding epsilon to 1 became exactly 1 after %d iterations\n", count);
   
   return 0;
}