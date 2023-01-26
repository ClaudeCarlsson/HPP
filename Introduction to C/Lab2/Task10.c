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
     printf("Enter a number:");
    scanf(" %d", &n);
    
    arr = (int *)malloc(n*sizeof(int));
    for(int i=0; i<n; ++i) arr[i] = rand() % 100; // random number from 0 to 99
    print_array(arr, n);
    return 0;
}