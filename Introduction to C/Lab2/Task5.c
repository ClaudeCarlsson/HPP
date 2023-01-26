#include <stdio.h>
#include <math.h>
int main() {

    int num;
    printf("Enter the calculation: ");
    scanf(" %d", &num);

    double num_d = sqrt((double)num);
    int num_i = num_d;

    if (num_d == num_i) {
        printf("True!");
    } else {
        printf("False!");
    }

    return 0;
}