#include <stdio.h>
#include <stdlib.h>

void swap_value(int *value_a, int *value_b)
{
    int temp = *value_a;
    *value_a = *value_b;
    *value_b = temp;
}

int partition(int *array, int lo, int hi)
{
    int pivot = array[lo];
    int i = lo - 1;
    for (int j = lo; j <= hi - 1; j++)
    {
        if (array[j] <= pivot)
        {
            i++;
            swap_value(&array[i], &array[j]);
        }
    }
    swap_value(&array[i + 1], &array[hi]);
    return i + 1;
}

void quicksort(int *array, int lo, int hi)
{
    if (lo < hi)
    {
        int p = partition(array, lo, hi);
        quicksort(array, lo, p - 1);
        quicksort(array, p + 1, hi);
    }
}

int check_input(int argc, char *argv[])
{
    if (!(argc == 2))
    {
        printf("Usage: %s <N> \n", argv[0]);
        return -1;
    }
    return 1;
}
void initialize_create_array(int N, int *array)
{
    for (int i = 0; i < N; i++)
    {
        array[i] = rand() % 100;
    }
}
void print_before_sorting(int *array)
{
    printf("Before sorting: ");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
void print_after_sorting(int *array)
{
    printf("After sorting: ");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int N = 0;
    if (check_input(argc, argv))
    {
        N = atoi(argv[1]);
    }
    else
    {
        return -1;
    }

    int *array = (int *)malloc(sizeof(int) * N);
    initialize_create_array(N, array);

    print_before_sorting(array);

    quicksort(array, 0, N - 1);

    print_after_sorting(array);

    return 0;
}
