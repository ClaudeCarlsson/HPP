#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int CmpDouble(const void* a, const void* b) {
    double x = *(const double *)a;
    double y = *(const double *)b;
    if (x < y) return -1;
    if (x > y) return 1;
}

int main() {
    double arrDouble[] = {9.3, -2.3, 1.2, -0.4, 2, 9.2, 1, 2.1, 0, -9.2};
    int arrlen=10;
    qsort (arrDouble, arrlen, sizeof(double), CmpDouble);
    for (int i = 0; i < arrlen; i++) {
        printf("%lf ", arrDouble[i]);
    }
    return 0;
}
