---
title: '6.5: Inter-task communication'
pre: "<i class='fas fa-book'></i> "
weight: 5
draft: true
---

## What's in a task ?

Up until this point a process and a thread were discussed



{{% notice error %}}
**!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! continue here !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**
{{% /notice %}}


. However, a better distinction is to be made. A **task** is a name that can cover both processes and threads. A process is, as was discussed in the previous chapter, an instance of a program that is running. Within a program multiple sequence streams could be written. Such a sequence stream within a process, is referred to with a **thread**. 

A process can run one single thread, or multiple threads. In all cases a process is a **standalone** unit. A thread, however, always belongs to process and is therefor not standalone.

When a process is divided into multiple threads, all threads share the same text, data, and bss segments with the process. The heap is also shared, but the stack is copied.

{{<figure src="/img/os4_proc_thread.png" title="Sections in a single threaded (left) and multithreaded (right) process.">}}

Note that, when running multile instances of a program, multiple processes are created. In contrast, when a program starts multiple threads, **no** additional processes are created.


## Hey task, it's me: task !

Having multiple tasks running is all good-and-well. Hey, it is one of the main reasons why the concept of an OS was introduced, remember ? Right, good job !! It would make sense though if different tasks were able to communicate with eachother. A distinction was made between multi-processes and multi-threading. Although both concepts are made for running multiple jobs, the communication between the jobs is much different in multi-processes and multi-threading.

### Multiple processes

1. signals
2. pipes
3. System V IPC
  * message queues
  * semaphores
  * shared memory


#### Signals
The first mechanism for interprocess communication (IPC) comes in the form of **signals**. This is the cheapest form of IPC. It litteraly allows one process to send a signal to another process, through the use of the function **kill()**. Although the name might be a bit misleading, it can be used to send all different signals. This function is to be used in programs, but it also has CLI-compatible command **kill**.

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

{{<todo message="Give example on > and <">}}

#### System V IPC
{{<todo message="Out-of-scope ?">}}

  * message queues
  * semaphores
  * shared memory

### Multiple threads


## Don't lock me out