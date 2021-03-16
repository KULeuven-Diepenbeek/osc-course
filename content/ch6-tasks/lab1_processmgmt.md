---
title: '6.2: Processes (lab)'
pre: "<i class='fas fa-vial'></i> "
weight: 2
---

{{<figure src="/img/os/db_pstree.png">}}
{{% dinobook %}}

## Creating and inspecting processes

**TIP:** the unistd.h header has some useful functions. You may also want to check out the `wait()` function in sys/wait.h and `exit()` in stdlib.h.

* Write a C-program that prints its own PID on the screen.

{{% figure src="/img/os/sc_621.png" title="An example output" %}}

* Write a C-program that spawns another process. Both parent and child processes announce their existence (through a printf) and their PIDs.

{{% figure src="/img/os/sc_622.png" title="An example output" %}}

* Write a C-program that creates 4 child processes
  * every of the childeren checks which numbers below 10000 are [prime](https://en.wikipedia.org/wiki/Prime_number)
  * every child reports only numbers that are prime (using printf), together with its own PID
  * before exiting, a child must announce how many prime numbers it has found in total
  * **TIP:** don't worry too much about the efficienty of calculating whether a number is prime or not. The calculation is meant to be time-consuming.
  * Answer this question: how are the processes scheduled? Do they all execute one after the other or at the same time? How can you tell? 

{{% figure src="/img/os/sc_623.png" title="An example output" %}}