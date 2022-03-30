#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define NUMBER_OF_THREADS 3

  // --------------------------------------
  // TODO: define one or more semaphores
  // --------------------------------------

void* king() {

  // --------------------------------------
  // TODO: sleep a random time, awake and signal the servants, sleep again
  // --------------------------------------

  return NULL;
}

void* servant(void * id) {
  int i;
  int * ptr_id = (int *) id;

  // --------------------------------------
  // TODO: wait for king to wake up, then printf() a message
  // --------------------------------------
  
  return NULL;
}

int main(void) {
  int i = 0, err;
  pthread_t tid[NUMBER_OF_THREADS];
  int thread_args[NUMBER_OF_THREADS];

  printf("Exercise 6.7.1 (with %d servants)\n", NUMBER_OF_THREADS-1);

  srand(time(NULL));

  // --------------------------------------
  // TODO: initialize one or more semaphores
  // --------------------------------------

  err = pthread_create(&(tid[0]), NULL, &king, NULL);
  if (err != 0) {
    printf("\ncan't create thread :[%s]", strerror(err));
  }

  for(i=1;i<NUMBER_OF_THREADS;i++){
    thread_args[i] = i;
    err = pthread_create(&(tid[i]), NULL, &servant, &thread_args[i]);
    if (err != 0) {
      printf("\ncan't create thread :[%s]", strerror(err));
    }
  }

  for(i=0;i<NUMBER_OF_THREADS;i++){
    pthread_join(tid[i], NULL);
  }
  
  // --------------------------------------
  // TODO: destroy one or more semaphores
  // --------------------------------------

  return 0;
}
