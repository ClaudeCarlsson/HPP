#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void swap_value(int *value_a, int *value_b)
{
    int temp = *value_a;
    *value_a = *value_b;
    *value_b = temp;
}

unsigned int partition(int *array, int lo, int hi)
{
    int pivot = array[hi];
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

void parallel_quicksort(int *array, int lo, int hi)
{
    if (lo < hi)
    {
        unsigned int p = partition(array, lo, hi);

#pragma omp task shared(array) firstprivate(lo, p)
        parallel_quicksort(array, lo, p - 1);
#pragma omp task shared(array) firstprivate(hi, p)
        parallel_quicksort(array, p + 1, hi);
#pragma omp taskwait
    }
}

int check_input(int argc, char *argv[])
{
    if (!(argc == 3))
    {
        printf("Usage: %s <N> <Threads> \n", argv[0]);
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

void print_before_sorting(int *array, int N)
{
    printf("Before sorting: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", array[i]);
    }
    printf("... ");
    for (int i = 5; i > 0; i--)
    {
        printf("%d ", array[N - (i + 1)]);
    }
    printf("\n");
}

void print_after_sorting(int *array, int N)
{
    printf("After sorting: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", array[i]);
    }
    printf("... ");
    for (int i = 5; i > 0; i--)
    {
        printf("%d ", array[N - (i + 1)]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int N = 0;
    int Threads = 0;
    if (check_input(argc, argv))
    {
        N = atoi(argv[1]);
        Threads = atoi(argv[2]);
    }
    else
    {
        return -1;
    }

    omp_set_num_threads(Threads);

    int *array = (int *)malloc(sizeof(int) * N);
    initialize_create_array(N, array);

    print_before_sorting(array, N);
#pragma omp parallel default(none) shared(array, N)
{
    #pragma omp single nowait
    parallel_quicksort(array, 0, N - 1);
} 
    print_after_sorting(array, N);

    free(array);
    
    return 0;
}
