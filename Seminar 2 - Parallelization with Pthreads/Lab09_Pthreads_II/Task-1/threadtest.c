#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int k = 10;

void* the_thread_func(void* arg) {
  int* p = malloc(sizeof(int) * k); // Dynamically allocate memory
  for (int i = 0; i < k; i++)
  {
    p[i] = i + 1;
  }
  pthread_exit((void*) p);
  //return (void*) p; // Return a pointer to the memory block
}

int main() {
  printf("This is the main() function starting.\n");

  /* Start thread. */
  pthread_t thread; // a pointer to the new thread that is being created
  printf("the main() function now calling pthread_create().\n");
  if(pthread_create(&thread, NULL, the_thread_func, NULL) != 0) {
    printf("ERROR: pthread_create failed.\n");
    return -1;
  }

  printf("This is the main() function after pthread_create()\n");

  /* Wait for thread to finish and retrieve the pointer to the memory block. */
  int* p;
  printf("the main() function now calling pthread_join().\n");
  if(pthread_join(thread, (void**) &p) != 0) {
    printf("ERROR: pthread_join failed.\n");
    return -1;
  }

  // Access the data and print it out
  printf("Data from the thread function: ");
  for (int i = 0; i < k; i++)
  {
    printf("%d ", p[i]);
  }
  printf("\n");
  // Free the dynamically allocated memory block
  free(p);

  return 0;
}