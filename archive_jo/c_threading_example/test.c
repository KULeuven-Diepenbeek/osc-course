#include <stdio.h>

#include <unistd.h> /* to use sleep() */
#include <stdlib.h> /* to use rand() */
#include <stdint.h> /* for intptr_t */

#include <pthread.h> /* to use threads */
#include <semaphore.h> /* to use semaphores */

#define NUMOF_PHILOSOPHERS 5

#define TIME_FACTOR .1
#define MAX_DURATION 10
#define NUMOF_ITERATIONS 100000

int spoons_int[NUMOF_PHILOSOPHERS];
sem_t spoons_sem[NUMOF_PHILOSOPHERS];

void *philosoper(void *vargp) {
  int i,j;
  int phil_id = (intptr_t)vargp;
  int timeout;

  for (i=0;i<NUMOF_ITERATIONS;i++) {
    /* start thinking */
    timeout = rand()%MAX_DURATION;
    //printf("    Philosopher %i starts thinking (%i s) ...\n", phil_id, timeout);
    printf("%iT\n", phil_id);
    sleep(timeout*TIME_FACTOR);
    //printf("    Philosopher %i stops thinking (%i s) ...\n", phil_id, timeout);
    
    /* try to pick up cutlery */
    timeout = rand()%MAX_DURATION;
    //printf("    Philosopher %i wants to eat (%i s) ...\n", phil_id, timeout);
    printf("%iW\n", phil_id);

    sem_wait(&spoons_sem[phil_id]);
    sem_wait(&spoons_sem[(phil_id-1+NUMOF_PHILOSOPHERS) % NUMOF_PHILOSOPHERS]);
    /* start eating */
    //printf("    Philosopher %i starts eating (%i s) ...\n", phil_id, timeout);
    printf("%iS\n", phil_id);
    sleep(timeout*TIME_FACTOR);
    /* put back cutlery */
    printf("%iS\n", phil_id);
    //printf("    Philosopher %i stops eating (%i s) ...\n", phil_id, timeout);
    sem_post(&spoons_sem[(phil_id-1+NUMOF_PHILOSOPHERS) % NUMOF_PHILOSOPHERS]);
    sem_post(&spoons_sem[phil_id]);
  }

  printf("Philosopher %i is done\n", phil_id);

  return NULL;
}

void *showSpoons() {
  int i;
  int value;

  while(1) {
    printf("S");
    for (i=0;i<NUMOF_PHILOSOPHERS;i++) {
      sem_getvalue(&spoons_sem[i], &value);
      //printf("  spoon_%i[%i] ", i, value);
      printf("%i", value);
    }
    printf("\n");
    sleep(1*TIME_FACTOR);
  }
}

int main(void) {
  int i,j;
  pthread_t tid[NUMOF_PHILOSOPHERS+1];

  /* place all the spoons_int */
  for (i=0;i<NUMOF_PHILOSOPHERS;i++) {
    spoons_int[i]=1;
    sem_init(&spoons_sem[i],0,1);
  }

  /* place all the philosophers */
  for(j=0;j<NUMOF_PHILOSOPHERS;j++){
    pthread_create(&tid[j], NULL, philosoper, (void *)(intptr_t)j);
  }
  /* start the monitor */
  pthread_create(&tid[NUMOF_PHILOSOPHERS], NULL, showSpoons, NULL);

  /* wait until they're done */
  for(j=0;j<NUMOF_PHILOSOPHERS;j++){
    pthread_join(tid[j], NULL);
  }

  /* remove the spoons */
  for(j=0;j<NUMOF_PHILOSOPHERS;j++){
    sem_destroy(&spoons_sem[i]);
  }

  /* stop the monitor */
  sleep(3*TIME_FACTOR);
  pthread_cancel(tid[NUMOF_PHILOSOPHERS]);

  printf("byebye\n");

  return 0;
}