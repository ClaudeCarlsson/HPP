#include <stdio.h>
#include <omp.h>

int main()
{
    // enable nested parallelism
    omp_set_nested(0);

// outer parallel block
#pragma omp parallel num_threads(2)
    {
        printf("Outer parallel block: Thread %d of %d\n", omp_get_thread_num(), omp_get_num_threads());

// inner parallel block
#pragma omp parallel num_threads(2)
        {
            printf("Inner parallel block: Thread %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
        }
    }

    return 0;
}
