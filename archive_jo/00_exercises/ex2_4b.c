#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int counter;
pthread_mutex_t lock_counter;

void* doSomeThing(void *arg) {
  unsigned long i = 0;

  pthread_mutex_lock(&lock_counter);
  counter += 1;

  printf("  Job %d started\n", counter);
  for(i=0; i<(0xFFFFFFFF);i++);
  printf("  Job %d finished\n", counter);

  pthread_mutex_unlock(&lock_counter);

  return NULL;
}

int main(void) {
  int i = 0, err;
  pthread_t tid[2];

  while(i < 2) {
    err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
    if (err != 0) {
      printf("\ncan't create thread :[%s]", strerror(err));
    }
    i++;
  }

  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);

  return 0;
}
