#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

static double get_wall_seconds()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

double **A, **B, **C;
int n;
int num_threads;

typedef struct
{
  int id;
  int start_row;
  int end_row;
} thread_data;

void *multiply(void *arg)
{
  thread_data *data = (thread_data *)arg;
  int i, j, k;
  for (i = data->start_row; i <= data->end_row; i++)
  {
    for (j = 0; j < n; j++)
    {
      for (k = 0; k < n; k++)
      {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  int i, j, k;

  if (argc != 3)
  {
    printf("Please give two arguments: the matrix size n and the number of threads\n");
    return -1;
  }

  n = atoi(argv[1]);
  num_threads = atoi(argv[2]);

  // Allocate and fill matrices
  A = (double **)malloc(n * sizeof(double *));
  B = (double **)malloc(n * sizeof(double *));
  C = (double **)malloc(n * sizeof(double *));
  for (i = 0; i < n; i++)
  {
    A[i] = (double *)malloc(n * sizeof(double));
    B[i] = (double *)malloc(n * sizeof(double));
    C[i] = (double *)malloc(n * sizeof(double));
  }

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
    {
      A[i][j] = rand() % 5 + 1;
      B[i][j] = rand() % 5 + 1;
      C[i][j] = 0.0;
    }

  printf("Doing matrix-matrix multiplication...\n");
  double startTime = get_wall_seconds();

  // Multiply C = A*B in parallel
  pthread_t threads[num_threads];
  thread_data thread_data_array[num_threads];

  // Determine the number of rows that each thread should handle
  int rows_per_thread = n / num_threads;

  // Divide the work among the threads
  for (i = 0; i < num_threads; i++)
  {
    // Set the thread's ID
    thread_data_array[i].id = i;

    // Determine the start and end rows for the thread
    thread_data_array[i].start_row = i * rows_per_thread;
    if (i == num_threads - 1)
    {
      thread_data_array[i].end_row = n - 1;
    }
    else
    {
      thread_data_array[i].end_row = (i + 1) * rows_per_thread - 1;
    }

    // Launch the thread
    if (pthread_create(&threads[i], NULL, multiply, &thread_data_array[i]))
    {
      printf("Error creating thread\n");
      return -1;
    }
  }

  for (i = 0; i < num_threads; i++)
  {
    pthread_join(threads[i], NULL);
  }

  double timeTaken = get_wall_seconds() - startTime;
  printf("Elapsed time: %f wall seconds\n", timeTaken);

  // Correctness check (let this part remain serial)
  printf("Verifying result correctness for a few result matrix elements...\n");
  int nElementsToVerify = 5 * n;
  double max_abs_diff = 0;
  for (int el = 0; el < nElementsToVerify; el++)
  {
    i = rand() % n;
    j = rand() % n;
    double Cij = 0;
    for (k = 0; k < n; k++)
      Cij += A[i][k] * B[k][j];
    double abs_diff = fabs(C[i][j] - Cij);
    if (abs_diff > max_abs_diff)
      max_abs_diff = abs_diff;
  }
  printf("max_abs_diff = %g\n", max_abs_diff);
  if (max_abs_diff > 1e-10)
  {
    for (i = 0; i < 10; i++)
      printf("ERROR: TOO LARGE DIFF. SOMETHING IS WRONG.\n");
    return -1;
  }
  printf("OK -- result seems correct!\n");

  // Free memory
  for (i = 0; i < n; i++)
  {
    free(A[i]);
    free(B[i]);
    free(C[i]);
  }
  free(A);
  free(B);
  free(C);

  return 0;
}
