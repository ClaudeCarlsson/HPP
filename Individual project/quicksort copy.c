#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void swap_value(int *value_a, int *value_b)
{
    int temp = *value_a;
    *value_a = *value_b;
    *value_b = temp;
}

int partition(int *array, int lo, int hi)
{
    int pivot = array[hi];
    int i = lo - 1;
#pragma omp parallel for schedule(static)
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
#pragma omp task firstprivate(array, lo, p)
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

    omp_set_num_threads(8);

    int *array = (int *)malloc(sizeof(int) * N);
    initialize_create_array(N, array);

#pragma omp parallel
    {
#pragma omp single nowait
        {
            quicksort(array, 0, N - 1);
        }
    }

    return 0;
}
