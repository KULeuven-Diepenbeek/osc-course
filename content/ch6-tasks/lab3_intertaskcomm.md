---
title: '6.6: Inter task communication (lab)'
pre: "<i class='fas fa-vial'></i> "
weight: 6
draft: true
---


!! DEPRECATED: SPLIT OUT INTO IPC and Inter-Thread separately !! 


{{<figure src="/img/os/header_communication.jpg" title="Source: G.I." >}}

## Inter thread communication

* Write a C-program that has 1 *king* thread and *n* *servant* threads. The number of threads should be configurable through a define. The king thread sleeps for a random amount of time and signals the servants when it awakes. All servant threads politely say **Good morning, sire** together with a servant ID. The king thread goes to sleep again.

    * the order of the servants **can** vary
    * every servant needs to greet the king **once** (no more, no less)
    * the king **doesn't** wait for the greetings before he goes back to sleep

{{% figure src="/img/os/sc_642.png" title="An example output" %}}

* **REVISIT, WITH A TWEAK** Write a C-program that has 1 *king* thread and *n* *servant* threads. The number of threads should be configurable through a define. The king thread sleeps for a random amount of time and signals the servants when it awakes. All servant threads politely say **Good morning, sire** together with a servant ID. The king thread goes to sleep again.

    * the order of the servants **can** vary
    * every servant needs to greet the king **once** (no more, no less)
    * the king **does** wait for the greetings before he goes back to sleep <-------------- here's the tweak

{{% figure src="/img/os/sc_642.png" title="An example output" %}}
