---
title: '6.3: Thread management'
pre: "<i class='fas fa-book'></i> "
weight: 3
draft: true
---

One of the three core tasks of an OS is the **management of tasks**. These different tasks are all running on the same processor. To make this magic happen some form of management is required.

## What's in a thread ?

A process can exist out of multiple **threads**. Up until now all the processes that were discussed contained one thread.

{{% figure src="/img/os/db_singlethreaded.png" title="The single threaded process" %}}
{{% dinobook %}}

Let's examine the image above. On the top of this image the following segments are mentioned: **code**, **data**, and **files**. Additionally the registers and the stack  are mentioned. These registers are the values of the registers that belong to the processor for this process. Such a process is referred to as a **single-threaded process**.

When multiple processes run, every process has **an image** like shown below. This means that multiple instances of the same program have **isolated** code segments, stack, ... . 

{{% figure src="/img/os/db_singlethreaded_twice.png" title="The single threaded process" %}}
{{% dinobook %}}

As can be learned from even looking at the name **multi-threaded** process, such a process has more than a single thread. It could be seen as multiple processes of the same process that share certain aspects. An image says more than a thousand words ... so below is a comparison between a single-threaded process and a multi-threaded process.
{{% figure src="/img/os/db_multithreaded.png" title="A single-threaded vs multi-threaded process" %}}
{{% dinobook %}}

<style>
  div.twocolumns {
    display: flex;
    flex-direction: row;
    justify-content: space-around;
  }
  div.column {
    width: 35%;
  }
  div.column ul {
    margin-top: 0px;
  }
</style>

<div class="twocolumns">
  <div class="column">
    The multiple threads in a multi-threaded process <b>share</b>:
    <ul>
      <li>the code segment</li>
      <li>the data segment</li>
      <li>the list of open files</li>
    </ul>
  </div>
  <div class="column">
    The multiple threads in a multi-threaded process <b>have unique</b>:
    <ul>
      <li>register content</li>
      <li>stacks</li>
      <li>program counters</li>
    </ul>
  </div>
</div>

## Why would we want multiple threads ?

There are 4 major benefits to working with multiple threads:

0. **Responsiveness**: When a single program is broken down into multiple threads the user experience feels more responsive. Dedicated threads can be created to handle user requests an give (visual) feedback.
0. **Resource sharing**: Programs that have multiple threads typically want some sort of communication between these threads. This is done more easily between threads than between processes.
0. **Economy**: Context switching becomes cheaper when switching between threads in comparison than switching between processes.
0. **Scalability**: Multiple threads can run in parallel on multi-core systems in contrast to a single threaded process.

{{% notice warning %}}
Although there are **many advantages** to multi-threaded programming, it requires **skilled programming** to cash in on these opportunities.
{{% /notice %}}

### Amdahl's law

At a scientific conference in 1967, the American researcher Gene Amdahl presented a paper that contained a formula. This formula identifies potential performance gains from adding additional computing cores to an application that has both serial and parallel components.

{{% mathjax %}}
speedup < { 1 \over { S + { (1-S) \over N } } }
{{% /mathjax %}}

In this formula **S** stands for the portion of the application that *has to be* run serially. **N** stands for the number of cores on which the parallel portion is spread.

{{% figure src="/img/os/amdahl.png" %}}

The graph above visualises Amdahl's law. For example, if a program has 80% of its code that can be run in parallel, it can be run maximally 2.5 times faster, using 4 cores. This point is marked with a red dot in the graph.

As stated above, it requires a skilled programmer to achieve maximal speed-up. If the program needs a lot of data that needs to be communicated between the serial and parallel portions this becomes even harder to achieve.


## Creating threads

In the previous section on processes, multiple processes could be created through the *fork* and *exec* functions. These function wrap the system-calls that are required to achieve this. Therefore, this comes intrinsically with the OS.

To allow multi-threading, an additional programmer API is required. There typically are 3 libraries that provide this:

0. Windows
0. Java
0. POSIX Pthreads

The Windows library is available only on Windows. The Java library is running on the Java Virtual Machine and translates the multi-threading requirements to the native requirements. Finally, Pthreads runs on Unix-y OSes like Linux, and iOS. 

An organisation, led by IEEE, has specified a set of standards and group these under the **POSIX** acronym (Portable Operating System Interface). The goal is to enhance portability of code between different systems. However, controversy exists around (parts of) this and discussing the pro-and-contra's falls out of the scope of this course. This can be added to the long list of "cultural wars" that still rage on, like:

* Emacs vs vi
* Linux vs Windows
* the "Final Browser War"
* ...


### Pthreads

An example for creating a new thread is given below. 
```C
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int counter;

void* doSomeThing() {
    unsigned long i = 0;
    counter += 1;

    printf("  Job %d started\n", counter);
    for(i=0; i<(0xFFFFFFFF);i++);
    printf("  Job %d finished\n", counter);

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

{{% task %}}
What will be the printed output of the C-code above ?
{{% /task %}}

{{% notice note %}}
When the code above get compiled, the **pthread** library has to be used. This library contains the object files that implemented the functions *pthread_create()* and *pthread_join()*. Compilation can be done because of the ```#include <pthread.h>``` line.
{{% /notice %}}

{{% figure src="/img/os/sc_compile.png" %}}

{{% task %}}
The code above is provided as boilerplate code in the Git-repository on the VM. Try to **compile** and **run** this code and see what the output is.
{{% /task %}}

## Inter-thread communication
One *raison d'être* for multi-threaded applications is **resource sharing**. In the example that is shown above this is done through a **global variable** 'counter'. Because no measures were taken this is exactly what goes wrong in that example. The output of the example looks like shown below.

{{% figure src="/img/os/sc_631.png" %}}

This might come as a surprise :smiley: <br/>
It should be clear that what we wanted to see was *Job 1 started* followed by *Job 1 finished* and that this would be repeated again for job number 2.

The first of both threads that gets to its function increments the counter from 0 to 1. However, before this thread has finished its execution, the second thread has started and has incremented the counter from 1 to 2. By the time the first thread finishes, the counter value is 2 in contrast with the expected value of 1.

### Mutex
The simplest form of solving inter-thread communication issues is the use of a mutex. This is a portmanteau of **Mut**ual **Ex**clusion. The behaviour can be seen as the lock on a toilet door. If you are using the toilet, you **lock** the door. Others that want to occupy the toilet have to wait until you're finished and you **unlock** the door (and get out).

The concept of a mutex is implemented in the pthreads library as a new variable type: **pthread_mutex_t**. Locking and unlocking can be done through functions **pthread_mutex_lock()** and **pthread_mutex_unlock()**.

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

This solves the issue that was encountered above.
{{% figure src="/img/os/sc_mutex.png" %}}

### Semaphore

A more advance technique for synchronisation, in comparison with a mutex, is a semaphore. To illustrate this, a semaphore can be thought of as a bowl with tokens. For example, in daycare there can be a room with toys. 

{{% figure src="https://media-cdn.tripadvisor.com/media/photo-s/03/c6/74/b4/cafe-boulevard.jpg" title="This photo of Cafe Boulevard is courtesy of Tripadvisor"  width="50%" %}}

Only 5 children are allowed in that room. Outside, there is a bowl with bracelets. When a child wants to enter the room to play, he/she needs to take a bracelet and put it on. When there are not more bracelets, the child has to wait until another child leaves the room and places the bracelet back in the bowl.

This technique is used in producer-consumer problems, amongst other. It is pointed out that if there is only a single token in the semaphore, this behaves exactly the same as a mutex. Such a semaphore is referred to as a **binary semaphore**.

The **pthreads** library also provides an API to program with semaphores. It contains functions like:

* sem_init()
* sem_wait()
* sem_trywait()
* sem_post()
* sem_getValue()

**TODO** **TODO** **TODO** **TODO** **TODO** 
https://techdifferences.com/difference-between-semaphore-and-mutex.html
**TODO** **TODO** **TODO** **TODO** **TODO** 