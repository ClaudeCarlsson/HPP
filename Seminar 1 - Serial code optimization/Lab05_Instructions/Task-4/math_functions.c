#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
   unsigned int i;
   float x, k;
   for (i=0; i<50000000; i++)
   {
      //x = pow(i, 0.5);
      //x = sqrtf(i);
      x = sqrtf(i);
   }
   printf("%f\n", x);
   return 0;
}
