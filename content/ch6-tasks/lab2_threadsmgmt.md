---
title: '6.4: Threads'
pre: "<i class='fas fa-vial'></i> "
weight: 4
---

{{<figure src="/img/os/db_threads.png">}}
{{% dinobook %}}

## Creating and inspecting threads

* Write a C-program that has 3 threads. Each thread announces its existence through a printf() together with its PID.

{{% figure src="/img/os/sc_641.png" title="An example output" %}}

* Write a C-program that has 1 *king* thread and *n* *servant* threads. The number of threads should be configurable through a define. The king thread sleeps for a random amount of time and signals the servants when it awakes. All servant threads politely say **Good morning, sire** together with a servant ID. The king thread goes to sleep again.

    * the order of the servants **can** vary
    * every servant needs to greet the king **once** (no more, no less)

{{% figure src="/img/os/sc_642.png" title="An example output" %}}

* Analyse exercise 6_4_3.c (shown below) and write a report (**<** 3 pages):
  1. describe what the program does 
  2. make a chart that plots 'the elapsed real time' the program consumes in function of the number of 'the number of threads that are contributing'
      * the scale on the X-axis goes from 2 to 300
      * at least 8 data points should be present in the chart
      * **TIP** the command [*time*](https://linux.die.net/man/1/time)
  3. interpret the chart
  4. there is a chance that multiple consumers handle the same number. Prevent this from happening !! Describe your solution in the report.

<center>**hand in the report AND the modified C file**</center>

```C
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h> 
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define NUMBER_OF_THREADS 5
#define MAX_COUNT 500000

static sem_t obj_produced;
static sem_t obj_consumed;

static int shelf;


void * producer() {
  int i;
  
  for(i=2; i< MAX_COUNT; i++) {
    shelf = i;
    sem_post(&obj_produced);
    sem_wait(&obj_consumed);
  }

  return NULL;
}


void * consumer() {
  unsigned char isPrime;
  int i;
  int VUT;

  while(1) {
    sem_wait(&obj_produced);
    VUT = shelf;
    sem_post(&obj_consumed);
    printf("[CONSUMER] %d\n", VUT);

    isPrime = 1;
    for (i=2;i<VUT; i++) {
      if (VUT % i ==0) {
        isPrime = 0;
      }
    }
    if(isPrime==1) {
      printf("    thread #x announces that %d is prime.\n", i);
    }
  }
}


int main(void) {
  int i = 0, err;
  pthread_t tid[NUMBER_OF_THREADS];

  // create semaphores
  err = sem_init(&obj_produced, 0, 0);
  if(err != 0) {
    printf("\ncan't create semaphore: obj_produced [%s]", strerror(err));
    return 1;
  }
  err = sem_init(&obj_consumed, 0, 0);
  if(err != 0) {
    printf("\ncan't create semaphore: obj_produced [%s]", strerror(err));
    return 1;
  }

  // create producer thread
  err = pthread_create(&(tid[i]), NULL, &producer, NULL);
  if (err != 0) {
    printf("\ncan't create producer thread: [%s]", strerror(err));
    return 1;
  } 
  printf("Producer thread created\n");

  // create consumer threads
  for(i=1;i<NUMBER_OF_THREADS;i++) {
    err = pthread_create(&(tid[i]), NULL, &consumer, NULL);
    if (err != 0) {
      printf("\ncan't create consumer thread %d: [%s]", i, strerror(err));
    }
    printf("Consumer thread %d created\n", i);
  }

  // wait for producer thread
  pthread_join(tid[0], NULL);

  // kill consumer threads 
  for(i=1;i<NUMBER_OF_THREADS;i++) {
    pthread_kill(tid[i], 9);
  }

  // delete the semaphores
  sem_destroy(&obj_produced);
  sem_destroy(&obj_consumed);

  return 0;
}

```
