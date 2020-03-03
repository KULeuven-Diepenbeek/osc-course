---
title: '6.1: Processes'
pre: "<i class='fas fa-book'></i> "
weight: 1
---

One of the three core tasks of an OS is the **management of tasks**. These different tasks are all running on the same processor. To make this magic happen some form of management is required.


## What's in a process ?

By definition, a process is an instance of a program. As was dicussed in the "C-portion" of this course a basic program can be divided in multiple **segments**. When source code is compiled into a binary, these segments are *fixed*. 

* **text/code**: is the machine code in assembly. This section is compiled for one (type of) processor(s).
* **data**: is the segment that contains initialised variables. These variables could be global, static, or external. A further distinction can be made between normal initialised variables and constants. This distinction is often referred to with read-only (**ro-data**) and read-write (**rw-data**), with the former the part where the constants reside and the latter that of the normal variables.
* **bss**: this segment contains the global and static variables that are not initialised.
* **stack**: *see next chapter*
* **heap**: *see next chapter*


Let's put these definitions to the test. A very simple program could be written as follows:
```C
#include <stdio.h>

int main(void) {

  printf("hello world !\n");

  return 0;
}

```

This program can be compiled with the command below:

```bash
jvliegen@localhost:~/$ gcc -o hello hello.c

jvliegen@localhost:~/$ 
```

On the CLI there is a command **size** that can be used to examine these segments. The arguments that are available on Linux commands can typically be explored with **command --help** or **man command** (offcourse, command needs to be replaced with the actual command-name).

```bash
jvliegen@localhost:~/$ size -B hello
   text    data     bss     dec     hex filename
   1516     600       8    2124     84c hello
jvliegen@localhost:~/$ 
```

This command shows the sizes of the sections that are discussed above. The text, data and bss sections are 1516, 600, and 8 bytes. In total this sums up to 2124 bytes, which can be written hexadecimally as 0x84C.

OK, this makes sense :)

## Run process !

By the time you're reading this part of the course, running the binary that was compiled above should be a walk in the park.

```bash
jvliegen@localhost:~/$ ./hello
hello world !

jvliegen@localhost:~/$ 
```

When a program is started, an **instance** of the program is created. This results (among many other things) in an allocation of the instance of the program in the memory. This means that the program is mapped somewhere in the memory space. How this mapping in the memory space is achieved will be discussed in [chapter 8](/osc-course/ch8-memory).

Next to mapping an instance of the program in memory space, upon start-up a **Process Control Block (PCB)** is created. 

### Process Control Block
The Process Control Block (PCB) is a representation of the process in the OS. It is created as a *task_struct* object. Such a PCB is made for every process and the definition of its struct is in the kernel source. 

**HOLD ON** Linux is an open source OS, so does that mean we should be able to find this struct in the source code ?

**WELL YES** Inspecting the [sched.h](https://github.com/torvalds/linux/blob/master/include/linux/sched.h) file verifies: 

1. that we **can** read the source code
2. that the **task_struct** is indeed there, 
3. that the PCB has **a lot** of parameters. The definition of the struct starts at line 624 and ends at line 1284 (at the moment of writing this course, Nov 15th 2019). As might be clear from this code (or even from thinking about the number of lines of codes), this struct is rather large. A (very) small subset of the fields in the struct represent:
  * the process state
  * the process identifier (PID)
  * the process priority
  * CPU scheduling info
  * list of open files
  * memory limits
  * CPU registers
  * program counter

The PCBs of all the processes are contained in a doubly-linked list which is headed by the **mother of all processes**. This process is called **init** and has **PID 0**. The doubly-linked list is commonly known as the **process table**.

Let's verify all of the above. We'll adapt the C program so it takes more time to run.

```C
#include <stdio.h>
#include <unistd.h>

#define DURATION_IN_MINUTES 2

int main(void) {
  int i;

  for(i=0;i<(DURATION_IN_MINUTES*60);i++) {
    printf("hello world !\n");
    sleep(1);
  }

  return 0;
}
```

After starting the program, the PID of the process can be looked for.

```bash
jvliegen@localhost:~/$ ./longhello
hello world !
hello world !
...
```

```bash
jvliegen@localhost:~/$ ps -u
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
jvliegen 14339  0.0  0.0  30408  5500 pts/3    Ss   09:57   0:00 bash
jvliegen 20162  0.0  0.0   4504   804 pts/1    S+   11:49   0:00 ./longhello
jvliegen 20244  3.0  0.0  47232  3616 pts/3    R+   11:51   0:00 ps -u
jvliegen 27675  0.0  0.0  30544  5556 pts/0    Ss+  08:55   0:00 bash
jvliegen 27700  0.2  0.5 207400 96300 pts/0    Sl   08:55   0:30 /usr/local/bin/
jvliegen 29414  0.0  0.0  30412  5504 pts/1    Ss   09:13   0:00 bash

...
```

Through the ps command the PID of the process **./longhello** can be found. In the example above it's 20162. While this process is running, there is a folder in the **/proc** map that has the same name as the PID. There is a lot of metadata on the process that can be consulted here. Also, certain fields in the struct_task are reflected in this folder. 

```bash
jvliegen@localhost:~/$ ls /proc/20162 
attr             exe        mounts         projid_map    status
autogroup        fd         mountstats     root          syscall
auxv             fdinfo     net            sched         task
cgroup           gid_map    ns             schedstat     timers
clear_refs       io         numa_maps      sessionid     timerslack_ns
cmdline          limits     oom_adj        setgroups     uid_map
comm             loginuid   oom_score      smaps         wchan
coredump_filter  map_files  oom_score_adj  smaps_rollup
cpuset           maps       pagemap        stack
cwd              mem        patch_state    stat
environ          mountinfo  personality    statm
jvliegen@localhost:~/$
```

Don't forget it's there !! It might come in handy someday !!
Every process has a PCB that contains metadata about the process.

### Process state
One of the fields in the PCB is the **process state**. This value can be set to any of these values:

* **New** The process is being created
* **Ready** The process is waiting to be assigned to a processor
* **Running** Instructions are being executed
* **Waiting** The process is waiting for some event to occur (such as an I/O completion or reception of a signal)
* **Terminated** The process has finished execution

{{% figure src="/img/os/db_processstate.png" title="The different process states and their transitions" %}}
{{% dinobook %}}


### Open files list
Every process that is created has a list of open files. Even programs that do not work with files have this list, and it **not empty**. Typically three files are open and these files are:

0. standard input (stdin)
0. standard output (stdout)
0. standard error (stderr)

By default, stdin is mapped to the keyboard and both stdout and stderr are mapped to the monitor. These mappings can be altered, however. Redirecting can be done and will be briefly touched in [section 6.5](/ch6-tasks/intertasks/).



## Creating processes

In Linux there are two typical ways for users to create processes: using **fork** or using **exec**. For the record, it is mentioned there is a third option using a system() function but because it is less secure and is less efficient then the other two, it is not discussed here.

Both fork and exec create a new process. The fork function copies the PCB of its process to a new PCB. The process that calls the fork() is referred to with the **parent** process while the new process is the **child** process. The child process will continue operations on the same line as the parent process. Because of the copying of the PCB, the program counter is also copied !!

The exec() function call also starts from copying its own PCB. In contrast with fork(), it then replaces the 'program' (read the *text*, *data*, and *bss*) with a new program and starts executing from (relative) 0.

It is mentioned earlier that the first process that is started is the **init** process. When the complete OS starts, the init process spawns a lot of other processes. There are processes that handle DHCP requests, processes that do logging, and so on. Using the **pstree** command we can see the processes in a tree, and have a visual representation of which child-parent relations there are between processes.

{{< figure src="/img/0x_31.png" title="An example of the pstree command. The left image shows the result of Linux on an embedded system. The right image shows the result of Linux running on a laptop" >}}
