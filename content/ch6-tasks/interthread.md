---
title: '6.6: Inter Thread communication'
pre: "<i class='fas fa-book'></i> "
weight: 6
---

**TODO: add critical section (register updates) and deadlock empire stuff**

## Communication between threads

One *raison d'être* for multi-threaded applications is **resource sharing**. In the example that was given [earlier](/ch6-tasks/threads/#pthreads) a **global variable** 'counter' was used. No measures were taken for securing this approach it went wrong in that example. The output of the example looks like shown below.

{{% figure src="/img/os/sc_631.png" %}}

This might come as a surprise :smiley: <br/>
It should be clear that what we wanted to see was *Job 1 started* followed by *Job 1 finished* and that this would be repeated again for job number 2.

The first of both threads that gets to its function increments the counter from 0 to 1. However, before this thread has finished its execution, the second thread has started and has incremented the counter from 1 to 2. By the time the first thread finishes, the counter value is 2 in contrast with the intended value of 1.

### Mutex
The simplest form of solving inter-thread communication issues is the use of a mutex. This is a portmanteau of **Mut**ual **Ex**clusion. The behaviour can be seen as the lock on a toilet door. If you are using the toilet, you **lock** the door. Others that want to occupy the toilet have to wait until you're finished and you **unlock** the door (and get out, after washing your hands). Hence, the mutex has only two states: one or zero, on or off, ...

The concept of a mutex is implemented in the pthreads library as a new variable type: **pthread_mutex_t**. Locking and unlocking can be done through functions **pthread_mutex_lock()** and **pthread_mutex_unlock()**. As always, read the documentation for the exact usage of these functions.

The example above can be rewritten using a mutex:

```C
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int counter;
pthread_mutex_t lock_counter;                   /* THIS LINE HAS BEEN ADDED */

void* doSomeThing(void *arg) {
    unsigned long i = 0;

    int id;                                     /* THIS LINE HAS BEEN ADDED */
    pthread_mutex_lock(&lock_counter);          /* THIS LINE HAS BEEN ADDED */
    counter += 1;
    id = counter;                               /* THIS LINE HAS BEEN ADDED */
    pthread_mutex_unlock(&lock_counter);        /* THIS LINE HAS BEEN ADDED */


    printf("  Job %d started\n", id);           /* THIS LINE HAS BEEN CHANGED */
    for(i=0; i<(0xFFFFFFFF);i++);
    printf("  Job %d finished\n", id);          /* THIS LINE HAS BEEN CHANGED */

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
```

This solves the issue that was encountered above. Before the counter is accessed the mutex is locked. This provides exclusive access. The counter is then incremented and copied in to variable *id*. Finally, the mutex is unlocked.

With this measure in place, the result is as was intended.
{{% figure src="/img/os/sc_mutex.png" %}}

**PROTIP:** It is pointed out that the time (directionally proportional the number of instructions) between locking and unlocking a mutex should be kept to a minimum. Other threads might be waiting for the mutex to become available.

### Semaphore

A more advance technique for synchronisation, in comparison with a mutex, is a semaphore. To illustrate this, a semaphore can be thought of as a bowl with tokens. For example, in daycare there can be a room with toys. 

{{% figure src="https://media-cdn.tripadvisor.com/media/photo-s/03/c6/74/b4/cafe-boulevard.jpg" title="This photo of Cafe Boulevard is courtesy of Tripadvisor"  width="50%" %}}

Only 5 children are allowed in that room. Outside, there is a bowl with bracelets. When a child wants to enter the room to play, he/she needs to take a bracelet and put it on. When there are not more bracelets, a child that also wants to play in the room has to wait until another child leaves the room and places his/her bracelet back in the bowl.

This technique is used in e.g. producer-consumer problems, amongst many other types. In contrast with the mutex, a semaphore can have multiple states. It is *number* of tokens. It is pointed out that if there is only a single token in the semaphore, this behaves exactly the same as a mutex. Such a semaphore is referred to as a **binary semaphore**.

The **pthreads** library also provides an API to program with semaphores. It contains, amongst others, functions like:

* sem_init(): initialises a semaphore
* sem_wait(): decrements the number inside of the semaphore. 
* sem_post(): increments the number inside of the semaphore.

Note that the ```sem_wait()``` function is blocking. If the value of the semaphore is set to zero, the thread waits until it can acquire a lock. There is a non-blocking alternative sem_trywait(). See the manual pages for more info and the correct usage.


Next to fact that a mutex only has a single token, where a semaphore can have more, the signalling is also a main difference. When a thread wants to get access to a semaphore and there are no more tokens available, it goes into a sleep-like state. When another thread produces a semaphore, a signal is sent to all the threads that were 'sleeping'.


More info on the differences between a semaphore and a mutex are given [here](https://techdifferences.com/difference-between-semaphore-and-mutex.html).