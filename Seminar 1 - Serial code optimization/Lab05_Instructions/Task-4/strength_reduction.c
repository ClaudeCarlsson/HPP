#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
   unsigned int i;
   unsigned int a = 1, b = 2, c = 3, d = 1;
   float x = 0.1, y = 0.5, z = 0.33, k;
   printf("%d %d %d %d, %f %f %f\n", a, b, c, d, x, y, z);

   for (i=0; i<50000000; i++)
   {
      c = d*2;
      b = c*15;
      a = b/16;

      k = 1/a;
      d = b*k;

      z = 0.33;
      y = 2*z;

      k = 1/1.33;
      x = y * k;

      k = 1/1.33;
      z = x * k;
   }
   printf("%d %d %d %d, %f %f %f\n", a, b, c, d, x, y, z);
   return 0;
}
