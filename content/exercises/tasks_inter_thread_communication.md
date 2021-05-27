---
title: '3. Inter-thread communication'
pre: "<i class='fas fa-pen-square'></i> "
weight: 3
---

Threading and inter-thread communication are complex topics that can be challenging to implement (correctly). However, even if you can use concepts like mutexes and semaphores without errors, it's still not always trivial to know *how to apply them to a specific problem*. Even for the well-known producer-consumer problem, several different setups are possible. 

This task requires you to think about the bigger picture and forces you to explain your thoughts in a concise and clear fashion. Some of the questions do not have a "single right answer" and/or are a bit vague: that is intentional. 

Analyse the code below and write a report (3-4 pages):

1. Describe the most important aspects of this program in terms of threading (in general, not line-by-line)
2. Note that this program does something similar to the prime-thread exercise (nr 3) in [Section 6.7](/ch6-tasks/lab3_interthreadcomm)
    * However, it is fundamentally different in how it divides the responsibilities between producers and consumers.
    * Explain this difference in detail. 
    * Discuss which of both approaches you think is probably more realistic / more likely to occur in practice and why.
3. Make a line chart that plots 'the elapsed time' the program consumes (y-axis) in function of 'the number of threads that are contributing' (x-axis)
    * For this, you change the NUMBER_OF_THREADS in the program to different values and re-run the program to observe the time it takes to complete
    * Note:
        * the scale on the X-axis goes from 2 to 300
        * don't just sample the number of threads between 2 and 300 uniformly though: be smart in how you choose your threadcounts!
        * at least 8 data points should be present in the chart
        * you can use any charting program for this (for example excel or google sheets)
        * **TIP** use the command [*time*](https://linux.die.net/man/1/time)
        * **NOTE** printf() can seriously slow down a program. Test this for yourself by running the timing tests with and without printf() statements.
        * **NOTE** it's best to execute each measurement a few times and on an unloaded system to get consistent results
4. Interpret the chart and draw conclusions
    * It is not sufficient to simply describe what's visible on the chart: you need to explain **WHY** this behaviour occurs.
5. Explain what would (probably) happen if you would use more than one producer thread (with MAX_COUNT divided between the threads)
    * Would the program run faster or slower? Why? 
    * Does it make sense to use multiple *producer* threads with this setup? Why (not)?
    * Does it make sense to use multiple *consumer* threads with this setup? Why (not)?
    * Answer both questions for the prime-thread exercise (nr 3) in [Section 6.7](/ch6-tasks/lab3_interthreadcomm) as well
    * For a different problem, how would you decide how to split the available number of threads between producers and consumers? 
6. The producer-consumer problem comes up in many other settings as well
    * Provide at least 2 examples of industrial (e.g., factory, logistics) or other real-world scenarios in which the producer-consumer problem occurs
    * Note: there aren't always literal "producers" or "consumers" of course; these are general concepts
        * For example, people in line at an amusement park can be seen as producers, while the park rides/rollercoasters are consumers
7. Include your solution (source code) for the prime-thread exercise (nr 3) in [Section 6.7](/ch6-tasks/lab3_interthreadcomm)
    * This is not part of the page-limit for the report of course ;)  

**Note that, like all other tasks, this is an individual assignment!**

Note: It's possible that you've solved exercise 6.7.3 (question 7 above) in group during class. 
In this case, you MUST add sufficient personal comments to the code that explain how it works and why the used approach was chosen.
You must also clearly list the students that collaborated on the code. 
This is to make it easier for the teaching team to assess if you actually understand the code or only copy-pasted it without contributing.
Submitting co-created code without such individual comments will be regarded as plagiarism and sanctioned. 
Note that this is only for question 7: questions 1-6 MUST be answered fully individually!

<center>**Hand in the report and the source code for the prime-thread exercise (together in a .zip file) via Toledo **</center>

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
