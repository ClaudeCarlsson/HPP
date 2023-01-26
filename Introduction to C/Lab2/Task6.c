#include <stdio.h>

int main() {

    int first, second;
    printf("Enter the numerator then the denominator: ");
    scanf(" %d %d", &first, &second);
    double remain;

    remain = first % second;

    printf(" %d / %d = %d With Remainder %.1lf \n\n", first, second, first / second, remain);

    return 0;

}