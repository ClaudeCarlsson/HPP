#include <stdio.h>
#include <pthread.h>

void* the_thread_func(void* arg) {
  double *data = (double *)arg;
  printf("In the_thread_func, data[0] = %lf, data[1] = %lf, data[2] = %lf\n", data[0], data[1], data[2]);
  return NULL;
}

int main() {
  printf("This is the main() function starting.\n");

  double data_for_thread[3];
  data_for_thread[0] = 5.7;
  data_for_thread[1] = 9.2;
  data_for_thread[2] = 1.6;

  /* Start thread. */
  pthread_t thread;
  printf("the main() function now calling pthread_create().\n");
  pthread_create(&thread, NULL, the_thread_func, data_for_thread);

  double data_for_thread_b[3];
  data_for_thread_b[0] = 9.6;
  data_for_thread_b[1] = 12.7;
  data_for_thread_b[2] = 4.1;

  /* Start thread. */
  pthread_t thread_b;
  printf("the main() function now calling pthread_create().\n");
  pthread_create(&thread_b, NULL, the_thread_func, data_for_thread_b);

  double data_for_thread_c[3];
  data_for_thread_c[0] = 52;
  data_for_thread_c[1] = 3546;
  data_for_thread_c[2] = 4356;

  /* Start thread. */
  pthread_t thread_c;
  printf("the main() function now calling pthread_create().\n");
  pthread_create(&thread_c, NULL, the_thread_func, data_for_thread_c);

  //printf("This is the main() function after pthread_create()\n");

  /* Do something here? */

  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join().\n");
  pthread_join(thread, NULL);
  pthread_join(thread_b, NULL);
  pthread_join(thread_c, NULL);

  return 0;
}
