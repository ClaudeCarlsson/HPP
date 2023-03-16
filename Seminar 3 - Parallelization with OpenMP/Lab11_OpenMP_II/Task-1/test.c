#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int a, b;
    a = 100;
    b = 20;

    printf("Initial value of a= %d\n", a);

    // Without data-sharing clauses
#pragma omp parallel
    {
        a += b;
        printf("Thread %d: a= %d b= %d\n", omp_get_thread_num(), a, b);
    }

    printf("Value of a after parallel loop without data-sharing clauses: %d\n", a);

    a = 100;

    // With firstprivate clause
#pragma omp parallel firstprivate(a)
    {
        a += b;
        printf("Thread %d: a= %d b= %d\n", omp_get_thread_num(), a, b);
    }

    printf("Value of a after parallel loop with firstprivate clause: %d\n", a);

    a = 100;

    // With lastprivate clause in a parallel loop
    int i, sum = 0;
#pragma omp parallel for firstprivate(a) lastprivate(sum)
    for (i = 0; i < 10; i++)
    {
        a += i;
        sum += a;
    }

    printf("Value of a after parallel loop with lastprivate clause: %d\n", a);
    printf("Value of sum after parallel loop with lastprivate clause: %d\n", sum);

    return 0;
}
