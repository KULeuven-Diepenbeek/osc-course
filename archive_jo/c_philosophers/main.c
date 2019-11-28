#include <stdio.h>
#include <pthread.h>  /* to use threads */
#include <stdint.h>   /* for intptr_t */
#include <stdlib.h>   /* for rand() */
#include <time.h>     /* for seeding rand() */
#include <unistd.h>   /* for sleep() */

#define MAX_COUNT  5000
#define NUMOF_PHILOSOPHERS 4
#define RAND_OFFSET 10 / 10

pthread_mutex_t mutexes[NUMOF_PHILOSOPHERS];

void * philosopherProcess(void * vargp) {
  int philosopher_id = *((int *)vargp);
  int i;
  float delay;
  
  for(i=0;i<MAX_COUNT;i++) {
    delay = ((rand()%9)+1) /10.0;
    printf("  philosopher %d starts thinking for %.3f seconds\n", philosopher_id, delay);
    sleep(delay);

    delay = ((rand()%9)+1) /10.0;
    // take spoon right
    printf("  philosopher %d wants to eat\n", philosopher_id);
    printf("  philosopher %d searches for the fork on the right\n", philosopher_id);
    pthread_mutex_lock(&mutexes[philosopher_id]);
    printf("  philosopher %d takes fork on the right\n", philosopher_id);
    // take spoon left
    printf("  philosopher %d searches for the fork on the left\n", philosopher_id);
    pthread_mutex_lock(&mutexes[(philosopher_id-1+4)%4]);
    printf("  philosopher %d takes fork on the left\n", philosopher_id);

    printf("  philosopher %d starts eating for %.3f seconds\n", philosopher_id, delay);
    sleep(delay);
    // return spoon right
    printf("  philosopher %d wants to stop eating\n", philosopher_id);
    printf("  philosopher %d returns the fork on the right\n", philosopher_id);
    pthread_mutex_unlock(&mutexes[philosopher_id]);
    // return spoon left
    printf("  philosopher %d returns the fork on the left\n", philosopher_id);
    pthread_mutex_unlock(&mutexes[(philosopher_id-1+4)%4]);
  }

  return NULL;
}

int main(void) {
  pthread_t tids[NUMOF_PHILOSOPHERS];
  int i_a[NUMOF_PHILOSOPHERS], i;

  for(i=0;i<NUMOF_PHILOSOPHERS;i++) {
    pthread_mutex_init(&mutexes[NUMOF_PHILOSOPHERS],NULL);
  }

  for(i=0;i<NUMOF_PHILOSOPHERS;i++) {
    i_a[i] = i;
    pthread_create(&tids[i], NULL, philosopherProcess, &i_a[i]);
  }

  for(i=0;i<NUMOF_PHILOSOPHERS;i++){
    pthread_join(tids[i], NULL);
  }
  
  for(i=0;i<NUMOF_PHILOSOPHERS;i++) {
    pthread_mutex_destroy(&mutexes[NUMOF_PHILOSOPHERS]);
  }

  printf("byebye\n");

  return 0;
}
