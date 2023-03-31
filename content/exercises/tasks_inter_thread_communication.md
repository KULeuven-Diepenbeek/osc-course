---
title: '3. Inter-thread communication'
pre: "<i class='fas fa-pen-square'></i> "
weight: 3
draft: true
---

Threading and inter-thread communication are complex topics that can be challenging to implement (correctly). However, even if you can use concepts like mutexes and semaphores without errors, it's still not always trivial to know *how to apply them to a specific problem*. Even for the well-known producer-consumer problem, several different setups are possible. 

Below, you will find an implementation variation on the prime-generator producer-consumer problem we handled during class (especially "Producer-Consumer V4: Semaphores" in [Section 6.7](/ch6-tasks/lab3_interthreadcomm)). As you will see, it is fundamentally different from the lab exercises in how it handles producer/consumer responsibilities. 

This task requires you to compare both approaches, to think about the bigger picture, and forces you to explain your thoughts in a concise and clear fashion. Some of the questions do not have a "single right answer" and/or are a bit vague: that is intentional. 

Analyse the code below and write a report (3-4 pages):

1. **Explain** the most important aspects of this program in terms of how it uses threading and inter-thread communication (in general, not line-by-line).
2. Explain the difference in how the program below and the "Producer-Consumer V4: Semaphores" exercise divide responsibilities between producers and consumers. Discuss which of both approaches you think is probably more realistic / more likely to occur in practice and why.
3. Make a line chart that plots 'the elapsed time' the program below consumes (y-axis) in function of 'the number of threads that are contributing' (x-axis)
    * For this, you change the NUMBER_OF_THREADS in the program to different values and re-run the program to observe the time it takes to complete
    * Note:
        * the scale on the X-axis goes from 2 to 300
        * don't just sample the number of threads between 2 and 300 uniformly though: be smart in how you choose your threadcounts!!!
        * at least 8 data points should be present in the chart
        * you can use any charting program for this (for example excel or google sheets)
        * **TIP** use the command [*time*](https://linux.die.net/man/1/time)
        * **NOTE** it's usually best to execute each measurement a few times and on an unloaded system to get consistent results
4. Interpret the chart and draw conclusions
    * It is not sufficient to simply describe what's visible on the chart: you need to explain **WHY** you think this behaviour occurs.
5. Explain what would (probably) happen if you would use more than one producer thread (with MAX_COUNT divided between the threads)
    * Would the program run faster or slower? Why? 
    * Does it make sense to use multiple *producer* threads with this setup? Why (not)?
    * Does it make sense to use multiple *consumer* threads with this setup? Why (not)?
    * Answer both questions for the "Producer-Consumer V4: Semaphores" exercise as well
    * In general, for a different problem, how would you decide how to split the available number of threads between producers and consumers? Why?
6. Include your solution (full source code with personal comments) for the "Producer-Consumer V4: Semaphores" exercise in [Section 6.7](/ch6-tasks/lab3_interthreadcomm)
    * This is not part of the page-limit for the report of course ;)  

**Note that, like all other tasks, this is an individual assignment!**

Still, it's possible that you've solved "Producer-Consumer V4: Semaphores" in group during class, which was allowed/recommended.

To be able to make sure however that each individual student **really** understands what the code does (and didn't just copy-paste it from someone else), you MUST add _sufficient_ **personal comments** in the code explaining the most important parts (how they work and why that approach was chosen). 

**Note that this all only counts for "Producer-Consumer V4: Semaphores" : questions 1-5 above MUST be answered fully individually!**

**Hand in the report (as a .pdf file!) and the source code for the "Producer-Consumer V4" exercise, together in a .zip file, via Toledo. Name it: BESC_task3_firstName_lastName.zip**.

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
