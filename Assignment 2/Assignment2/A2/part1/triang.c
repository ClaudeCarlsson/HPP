#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // User error, not correct inputs
    if (argc != 2) {
        printf("Usage: %s <number of lines> \n", argv[0]);
        return 1;
    }

    // Convert input to integer
    int lines;
    lines = atoi(argv[1]);

    // 0, special case
    int coef = 1;
    if (lines == 0) {
        //printf("%d ", coef);
        // Create new row
        //printf("\n");
        return 0;
    } else {

        // Create the triangle
        for (int i = 0; i < lines; i++) {
            coef = 1;
            for (int j = 0; j <= i; j++) {
                printf("%d ", coef);
                coef = coef*(i-j)/(j+1);
            }
            
            // Create new row
            printf("\n");
        }
    }
    return 0;
}