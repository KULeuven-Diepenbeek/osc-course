---
title: '6.4: Threads (lab)'
pre: "<i class='fas fa-vial'></i> "
weight: 4
---

{{<figure src="/img/os/db_threads.png">}}
{{% dinobook %}}

## Creating and inspecting threads

* Write a C-program that has 3 threads. Each thread announces its existence through a printf() together with its PID.

{{% figure src="/img/os/sc_641.png" title="An example output" %}}

* Write a C-program that has 1 *king* thread and *n* *servant* threads. The number of threads should be configurable through a define. The king thread sleeps for a random amount of time and signals the servants when it awakes. All servant threads politely say **Good morning, sire** together with a servant ID. The king thread goes to sleep again.

    * the order of the servants **can** vary
    * every servant needs to greet the king **once** (no more, no less)
    * the king **doesn't** wait for the greetings before he goes back to sleep

{{% figure src="/img/os/sc_642.png" title="An example output" %}}
