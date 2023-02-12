/**********************************************************************
 * Enumeration sort with task-based parallelism
 *
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define NUM_THREADS	8
#define LEN 100000
#define TASK_SIZE	(LEN / NUM_THREADS)

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

double indata[LEN], outdata[LEN];

struct Task {
  int start;
  int end;
};

void *findranks(void *arg) {
  struct Task *task = (struct Task*) arg;

  for (int i = task->start; i < task->end; i++) {
    int rank = 0;
    for (int j = 0; j < LEN; j++) {
      if (indata[j] < indata[i]) rank++;
    }
    outdata[rank] = indata[i];
  }

  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  pthread_t threads[NUM_THREADS];
  pthread_attr_t attr;
  struct Task tasks[NUM_THREADS];
  void *status;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);	

  // Generate random numbers
  for (int i = 0; i < LEN; i++) {
    indata[i] = drand48();
    outdata[i] = -1.0;
  }

  // Enumeration sort
  double startTime = get_wall_seconds();
  for (int i = 0; i < NUM_THREADS; i++) {
    int start = i * TASK_SIZE;
    int end = start + TASK_SIZE;

    tasks[i] = (struct Task) {start, end};
    pthread_create(&threads[i], &attr, findranks, (void*) &tasks[i]);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], &status);
  }
  double timeTaken = get_wall_seconds() - startTime;
  printf("Time: %f  NUM_THREADS: %d\n", timeTaken, NUM_THREADS);

  // Check results, -1 implies data same as the previous element
  for (int i = 0; i < (LEN - 1); i++) {
    if (outdata[i] > outdata[i+1] && outdata[i+1] > -1) {
      printf("ERROR: %f,%f\n", outdata[i], outdata[i+1]);
    }
  }

  return 0;
}