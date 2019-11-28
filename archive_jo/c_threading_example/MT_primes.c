#include <stdio.h>
#include <pthread.h>  /* to use threads */
#include <stdint.h>   /* for intptr_t */
#include <unistd.h>   /* for getpid()*/

#define MAX_COUNT  10000
#define NUMOF_CHILDREN 4

void * ChildProcess_v2(void * vargp) {
  int i, j, isPrime, counter=0;
  int child_id = (intptr_t)vargp;
  pid_t pid = getpid();

  for (i = 2; i <= MAX_COUNT; i++) {
    isPrime = 1;
    for (j = 2; (j <= i/2)&&(isPrime==1); j++) {
      if (i % j==0) {
        isPrime = 0;
      }
    }
    if(isPrime==1) {
      printf("   child (PID=%d, child ID=%d) announces that %d is prime.\n", pid, child_id, i);
      counter += 1;
    }
  }

  printf("   *** Child ID %d is done. Found %d primes under %d. ***\n\n", child_id, counter, MAX_COUNT);
  return NULL;
}

int main(void) {
  pthread_t tids[NUMOF_CHILDREN];
  int i;

  for(i=0;i<NUMOF_CHILDREN;i++) {
    pthread_create(&tids[i], NULL, ChildProcess_v2, (void *)(intptr_t)i);
  }

  for(i=0;i<NUMOF_CHILDREN;i++){
    pthread_join(tids[i], NULL);
  }
  
  printf("byebye\n");

  return 0;
}
