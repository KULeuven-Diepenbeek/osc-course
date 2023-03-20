---
title: '6.2: Processes (lab)'
pre: "<i class='fas fa-vial'></i> "
weight: 2
---

{{<figure src="/img/os/db_pstree.png">}}
{{% dinobook %}}

## Creating and inspecting processes

**TIP:** the unistd.h header has some useful functions. You may also want to check out the `wait()` function in sys/wait.h and `exit()` in stdlib.h.

### 6.1 PID info

Write a C-program that prints its own PID on the screen.

{{% figure src="/img/os/sc_621.png" title="An example output" %}}

### 6.2 Testing the waters with `fork()`

Write a C-program that spawns another process using `fork()`. Both parent and child processes announce their existence (through a printf) and their PIDs.

{{% figure src="/img/os/sc_622.png" title="An example output" %}}

### 6.3 Multiple `fork()` children

Write a C-program that creates 4 child processes using `fork()`, where:

+ each of the childeren checks which numbers below 10000 are [prime](https://en.wikipedia.org/wiki/Prime_number)
+ every child reports only numbers that are prime (using printf), together with its own PID
+ before exiting, a child must announce how many prime numbers it has found in total
+ **TIP:** don't worry too much about the efficienty of calculating whether a number is prime or not. The calculation is meant to be time-consuming.
+ Answer this question: how are the processes scheduled? Do they all execute one after the other or at the same time? **How can you tell?** 

{{% figure src="/img/os/sc_623.png" title="An example output" %}}

### 6.4 I `fork()`ed the `fork()`!

Given the following C code:

```c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    fork();
    fork();
    fork();
    fork();
    printf("Hi class\n");
    return 0;
}
```

How many times will `Hi class` be printed? Why? Draw a `pstree` tree that visualizes the parent and children to help explain your answer. 


### 6.5 `fork()` and order

Write two functions: a `main()` that calls another `void` function in which you `fork()` the process. If the resulting process is the child one, print some text. If it's the parent process, print another text. 

Execute the program from your commandline terminal a few hundred (!) times and carefully inspect the order of the printed messages. Are these always the same? If so, do you think this will always be the case for everyone running your specific hardware? Why (not)? **TIP**: Who decides the execution order and timing? 
