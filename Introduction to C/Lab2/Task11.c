#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_array (int arr[], int n) {
    int i = 0;
    while (i < n) {
        printf(" %d\n", arr[i]);
        i++;
    }
}

int main() {
    int *arr;
    int n;
    int i = 0;
    printf("Enter a number: ");
    int size = 10;
    arr = (int *)malloc(size*sizeof(int));

    while (scanf(" %d", &n) == 1) {
    printf("Enter a number: ");
        if (i % 10 == 9) {
            arr = (int *)realloc(arr, size*sizeof(int));
        }
        arr[i] = n;
        i++;
    }
    print_array(arr, i);
    return 0;
}