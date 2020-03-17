---
title: '6.6: Inter task communication (lab)'
pre: "<i class='fas fa-vial'></i> "
weight: 6
draft: true
---

{{<figure src="/img/os/header_communication.jpg">}}

## Inter process communication

{{% notice note %}}
These exercises are to be done in a terminal, using the command line interface.
{{% /notice %}}

* Open two terminals. On one terminal you start a process that takes some minutes to finish. From the other terminal:

  0. figure out the **process ID** of the first process
  0. send a **kill** signal to that first process.

* Use unnamed pipes to display all the processes of which you are the owner. From these processes only display the PID and the first 10 characters of the process's name. From this list only show the first 10 processes (not the first 10 lines !!)

{{% figure src="/img/os/sc_662.png" title="An example output" %}}

* **REVISIT, WITH A TWEEK** Write a C-program that has 1 *king* thread and *n* *servant* threads. The number of threads should be configurable through a define. The king thread sleeps for a random amount of time and signals the servants when it awakes. All servant threads politely say **Good morning, sire** together with a servant ID. The king thread goes to sleep again.

    * the order of the servants **can** vary
    * every servant needs to greet the king **once** (no more, no less)
    * the king **does** wait for the greetings before he goes back to sleep <-------------- here's the tweak

{{% figure src="/img/os/sc_642.png" title="An example output" %}}
