#include <stdio.h>
#include <pthread.h>  /* to use threads */
#include <stdint.h>   /* for intptr_t */
#include <unistd.h>   /* for getpid()*/

#define MAX_COUNT  10000
#define NUMOF_CHILDREN 4

int target;
pthread_mutex_t lock_counter;

void * ChildProcess_v2(void * vargp) {
  int i, j, isPrime, counter=0;
  int child_id = (intptr_t)vargp;
  pid_t pid = getpid();
  int mytarget;

  pthread_mutex_lock(&lock_counter);
  mytarget = target;
  target += 1;
  pthread_mutex_unlock(&lock_counter);

  while (mytarget < MAX_COUNT) {
    isPrime = 1;
    for (j = 2; (j <= mytarget/2)&&(isPrime==1); j++) {
      if (mytarget % j==0) {
        isPrime = 0;
      }
    }
    if(isPrime==1) {
      printf("   child (PID=%d, child ID=%d) announces that %d is prime.\n", pid, child_id, mytarget);
      counter += 1;
    }

    pthread_mutex_lock(&lock_counter);
    mytarget = target;
    target += 1;
    pthread_mutex_unlock(&lock_counter);
  }

  printf("   *** Child ID %d is done. Found %d primes under %d. ***\n\n", child_id, counter, MAX_COUNT);
  return NULL;
}

int main(void) {
  pthread_t tids[NUMOF_CHILDREN];
  int i;

  target = 2;

  for(i=0;i<NUMOF_CHILDREN;i++) {
    pthread_create(&tids[i], NULL, ChildProcess_v2, (void *)(intptr_t)i);
  }

  for(i=0;i<NUMOF_CHILDREN;i++){
    pthread_join(tids[i], NULL);
  }
  
  printf("byebye\n");

  return 0;
}
