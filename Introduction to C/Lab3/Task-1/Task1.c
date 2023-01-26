#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main() { 
    int *arr;
    int n = 0;
    printf("Enter array size: ");
    scanf(" %d", &n);
    int array[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            array[i][j] = -1;
            array[j][i] = -array[i][j];
        }
        array[i][i] = 0;
    }


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf(" %d  ", array[i][j]);
        }
        printf("\n");
    }

    return 0;
}

