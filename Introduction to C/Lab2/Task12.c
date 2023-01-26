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

int primenumber(int number)
{
    int i;
    
    for (i = 2; i <= number / 2; i++) {
        if (number % i != 0)
            continue;
        else
            return 1;
    }
    return 0;
}

int main() {
    int *arr;
    int n;
    int i = 0;

    int size;
    printf("Enter array size: ");
    scanf(" %d", &size);
    arr = (int *)malloc(size*sizeof(int));

    while (i < size) {
        scanf(" %d", &n);
        arr[i] = n;
        i++;
    }
    int *arr_nop;
    arr_nop = (int *)malloc(i*sizeof(int));
    int new_counter = 0;
    for (int k = 0; k < i; k++) {
        int res = primenumber(arr[k]);
        if (res == 1) {
            arr_nop[new_counter] = arr[k];
            new_counter++;
        } 
    }

    print_array(arr_nop, new_counter);
    return 0;
}