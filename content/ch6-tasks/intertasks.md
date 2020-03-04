---
title: '6.5: Inter task communication'
pre: "<i class='fas fa-book'></i> "
weight: 5
draft: true
---

Having multiple tasks running is all good-and-well. Hey, it is one of the main reasons why the concept of an OS was introduced, remember ? Right, **good job !!**

It would make sense, though, if different tasks were able to communicate with eachother. A distinction should be made between multi-processes and multi-threading. Although both techniques are made for running multiple jobs, the communication between the jobs is much different in both.


## Communication between processes

There are two main techniques to facilitate communication between multiple processes. These two techniques are shown in image below.

1. Shared memory
2. Message passing

{{% figure src="/img/os/db_ipc.png" title="The two main techniques for inter process communication" %}}
{{% dinobook %}}

### 1. Shared memory

When two processes communicate through shared memory, they have to be aware that the memory is **not** protected by the OS. One of the reasons why there are multiple processes is to certain tasks from other tasks. This protection is normally provided by the OS. An example is given below.


{{% figure src="/img/os/sc_stacksmashing.png" title="An example of memory protection that given by the OS" %}}


```C
#include <stdio.h>

int main(void) {
  int i, my_array[8];

  for(i=0;i<=8;i++) {
    my_array[i] = i+1;
  }

  for(i=0;i<8;i++) {
    printf("%d\n", my_array[i]);
  }

  return 0;
}
```

A programming API for using shared memory is provided by POSIX. The example below shows a **producer** on the left and a **consumer** on the right.

<div class="multicolumn">
  <div class="column">
  {{< highlight c >}}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>

int main() {
  const int SIZE = 4096; /* buffersize (bytes) */
  const char *name = "OS"; /* shared memory object name */
  const char *message_0 = "Hello"; /* message 1 */
  const char *message_1 = "World!"; /* message 2*/
  int shm_fd; /* file descriptor */
  void *ptr;

  /* create the shared memory object */
  shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

  /* configure the size of the shared memory object */
  ftruncate(shm_fd, SIZE);

  /* memory map the shared memory object */
  ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

  /* write to the shared memory object */
  sprintf(ptr,"%s",message_0);
  ptr += strlen(message_0);
  sprintf(ptr,"%s",message_1);
  ptr += strlen(message_1);




  return 0;
}
  {{< /highlight >}}
  </div>
  <div class="column">
  {{< highlight c >}}
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>


int main() {
  const int SIZE = 4096; /* buffersize (bytes) */
  const char *name = "OS"; /* shared memory object name */


  int shm_fd; /* file descriptor */
  void *ptr;

  /* open the shared memory object */
  shm_fd = shm_open(name, O_RDONLY, 0666);




  /* memory map the shared memory object */
  ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);


  /* read from the shared memory object */
  printf("%s",(char *)ptr);



  /* remove the shared memory object */
  shm_unlink(name);

  return 0;
}
  {{< /highlight >}}
  </div>
</div>
{{% dinobook %}}


### 2. Message passing

#### Signals
One mechanism for interprocess communication (IPC) comes in the form of **signals**. This is the cheapest form of IPC. It litteraly allows one process to send a signal to another process, through the use of the function **kill()**. Although the name might be a bit misleading, it can be used to send all different signals. This function is to be used in programs, but it also has CLI-compatible command **kill**.

```bash
jvliegen@localhost:~/$ kill -L
 1) SIGHUP   2) SIGINT   3) SIGQUIT  4) SIGILL   5) SIGTRAP
 6) SIGABRT  7) SIGBUS   8) SIGFPE   9) SIGKILL 10) SIGUSR1
11) SIGSEGV 12) SIGUSR2 13) SIGPIPE 14) SIGALRM 15) SIGTERM
16) SIGSTKFLT 17) SIGCHLD 18) SIGCONT 19) SIGSTOP 20) SIGTSTP
21) SIGTTIN 22) SIGTTOU 23) SIGURG  24) SIGXCPU 25) SIGXFSZ
26) SIGVTALRM 27) SIGPROF 28) SIGWINCH  29) SIGIO 30) SIGPWR
31) SIGSYS  34) SIGRTMIN  35) SIGRTMIN+1  36) SIGRTMIN+2  37) SIGRTMIN+3
38) SIGRTMIN+4  39) SIGRTMIN+5  40) SIGRTMIN+6  41) SIGRTMIN+7  42) SIGRTMIN+8
43) SIGRTMIN+9  44) SIGRTMIN+10 45) SIGRTMIN+11 46) SIGRTMIN+12 47) SIGRTMIN+13
48) SIGRTMIN+14 49) SIGRTMIN+15 50) SIGRTMAX-14 51) SIGRTMAX-13 52) SIGRTMAX-12
53) SIGRTMAX-11 54) SIGRTMAX-10 55) SIGRTMAX-9  56) SIGRTMAX-8  57) SIGRTMAX-7
58) SIGRTMAX-6  59) SIGRTMAX-5  60) SIGRTMAX-4  61) SIGRTMAX-3  62) SIGRTMAX-2
63) SIGRTMAX-1  64) SIGRTMAX  
jvliegen@localhost:~/$  
```

Two shortcuts are typically available in the CLI that allow for the sending of signals: CTRL+C and CTRL+Z. The former sends a SIGINT signal while the latter sends a SIGTSTP signal.

Let's illustrate this with an example.

```C
#include <stdio.h>
#include <unistd.h>

#define DURATION_IN_MINUTES 10

int main(void) {
  int i = DURATION_IN_MINUTES * 60;

  for(;i>=0;i--) {
    printf("TIMER: 00:%02d:%02d\n", (int)((i-i%60)/60), i%60);
    sleep(1);
  }

  return 0;
}
```

This program will emulate an egg timer. Every second it displays how much time is left. Once the process starts running, it takes 10 minutes to complete. This process can be **killed** by just pressing CTRL+C.

```bash
jvliegen@localhost:~/$ ./eg4_timer.bin 
TIMER: 00:10:00
TIMER: 00:09:59
TIMER: 00:09:58
TIMER: 00:09:57
TIMER: 00:09:56
^C
jvliegen@localhost:~/$ 

```

Another way to kill the process would be to explictly send the signal through the kill command. To use this command, the PID is needed. Through a new CLI-window, this PID has to be search for first. Note that the type of signal is an argument in the command.

```bash
jvliegen@localhost:~/$  ps ux | grep timer
jvliegen  5041  0.0  0.0   4504   772 pts/1    S+   06:04   0:00 ./eg4_timer.bin
jvliegen  5066  0.0  0.0  21996  1080 pts/2    S+   06:05   0:00 grep --color=auto timer
jvliegen@localhost:~/$  kill -KILL 5041
jvliegen@localhost:~/$ 
```

Allthough there numerous uses for sending signals between signals, one more example is interesting to have a closer look at. Above there was already some hinting to the CTRL+Z. 

The CLI is running a shell, as you already know by now. This is just a single interface. If you were to start a program, that CLI is occupied. Imagine you are working remotely on a server (through ssh), this would require you to open up a new connection to the server and have a second bash at your diposal. A more convenient solution would be to send the running program to the **background**.

```bash
jvliegen@localhost:~/$ xeyes 
```

Before you can send processes to the background, the process has to be halted first. This can be done through the CTRL+Z shortcut. With a halted process, the command **bg** sends it to the background. If you do not send it to the background, the process will *freeze*. Once it is in the background it continues running. Additionally, this would give you back your shell.

```bash
jvliegen@localhost:~/$ xeyes 
^Z
[1]+  Stopped                 xeyes
jvliegen@localhost:~/$ bg
[1]+ xeyes &
jvliegen@localhost:~/$ 
```

For the sake of completeness we enumerate a few more usefull aspects about this:

* a process can be started in the background as well. This can be achieved by adding an **ampersand** after the command: eg. xeyes &
* the command **jobs** gives you an overview of which jobs are running in the background
* through the command **fg <#>** the job with index number <#> will pulled to foreground.


#### Pipes
Another option to achieve inter-process communication is through **pipes**. There are two different types of pipes available:
* anonymous pipes
* named pipes

**Anonymous pipes** are like tubes with two ends. Communication is half-duplex, to that means one direction only. A pipe could be attached to a process through a file descriptor. One process could **write** into the pipe, while the other could **read** out of the pipe. This type of pipe can only be create between two processes that have parent-child relation ship. 

When using the CLI, pipes are a very powerful tool for chaining different commands. The output of the first commands will be the input for the next command.

```bash
jvliegen@localhost:~/$ xeyes &
jvliegen@localhost:~/$ ps u | grep xeyes | head -1 | cut -d " " -f 3
5526
jvliegen@localhost:~/$ 
```

The example above chains the following:

1. give a list of all *my* processes
2. only filter the lines that contain the word *xeyes*
3. filter only the first line 
4. split the input on a " " (a space) and report only the third field

**Named pipes** are the other type of pipes that can be created. The main difference is the lifetime of this mechanism. The **anonymous** pipes above only lived as long as the processes live. Named pipes have to be closed explictly (or at shutdown).

Anonymous pipes are use heavily on a **CLI**. Do you remember the Process Control Block ? This has one field called **list of open files** ... 


#### System V IPC
{{<todo message="Out-of-scope ?">}}

  * message queues
  * semaphores
  * shared memory

### Multiple threads


## Don't lock me out


Open files list

* process < STDIN 1>STDOUT 2>STDERR
* process < STDIN 1>STDOUT 2>&1

{{% figure src="/img/os/sc_redirect_stdout.png" title="Redirection of the standard output " %}}



## Communication between threads


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


{{% notice error %}}
**!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! continue here !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**
{{% /notice %}}


. However, a better distinction is to be made. A **task** is a name that can cover both processes and threads. A process is, as was discussed in the previous chapter, an instance of a program that is running. Within a program multiple sequence streams could be written. Such a sequence stream within a process, is referred to with a **thread**. 

A process can run one single thread, or multiple threads. In all cases a process is a **standalone** unit. A thread, however, always belongs to process and is therefor not standalone.

When a process is divided into multiple threads, all threads share the same text, data, and bss segments with the process. The heap is also shared, but the stack is copied.

{{<figure src="/img/os4_proc_thread.png" title="Sections in a single threaded (left) and multithreaded (right) process.">}}

Note that, when running multile instances of a program, multiple processes are created. In contrast, when a program starts multiple threads, **no** additional processes are created.

