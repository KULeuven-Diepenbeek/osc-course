---
title: '6.7: Inter-Thread communication (lab)'
pre: "<i class='fas fa-vial'></i> "
weight: 7
---

{{<figure src="/img/os/header_communication.jpg" title="Source: G.I." >}}

* Write a C-program that has 1 *king* thread and *n* *servant* threads. The number of servant threads should be configurable through a define. The king thread sleeps for a random amount of time (a few seconds) and signals the servants when it awakes. All servant threads politely say **Good morning, sire** together with a servant ID. The king thread goes to sleep again.

    * Every servant needs to greet the king **once** (no more, no less)
    * The king **doesn't** wait for the greetings before he goes back to sleep
    * You do not need to make sure that the servants always reply in the same order
    * Repeat the wake-greet cycle at least 5 times
    * Tip: use the ```rand()``` function to get random numbers

* **REVISIT, WITH A TWEAK** Change the previous king-servant setup with a single change: now, the king **does** explicitly wait for the greetings of _all_ his servants before he goes back to sleep.

{{% figure src="/img/os/sc_642.png" title="An example output" %}}

* Let's revisit the prime numbers for one last time. Like the prime-exercise in the previous lab, we will have 4 separate threads, each calculating a subsection of primes between 2 and N. Now however, we will not have each thread store their full results in thread-specific memory. Instead, each prime-calculting thread (the producers) communicates each discovered prime **as soon as possible** back to a separate "processing" entity that prints the primes to the screen (one or several consumers). Again, this can be accomplished in several different ways:

    1. You can use a single shared array and a shared counter (indicating how many items are in the array) to store the results
        * Access to the array is protected by a Mutex that both the producers and consumer(s) lock
        * Extra points if you can think of a way to not make this array take up excessive memory by the time the calculations are done
    2. You can pass each prime as an individual value between producer/consumer threads instead of using a shared array
        * Here, you can use Semaphores and/or Mutexes to coordinate this communication
            * Tip: ```sem_trywait()``` might be useful here, depending your approach
        * Extra points if you can think of a way of keeping the producers producing (at least for a small amount of time) while all consumers are busy

    * Tip: the complexity of the solution is of course higher if there are multiple consumer threads. You can start by using a single consumer thread, then extending it to use multiple.

    * The goal is to implement **one** of these options (you choose), think deeply about the rest, and then answer the following questions:
        * Which approach should be faster: this one with shared memory/direct value passing or the one from the previous lab using per-thread memory?
        * Which tradeoffs were made here in comparison with the previous version? (e.g., faster but less flexible, slower but less memory, ...)
        * Are you able to keep the primes sorted in this new version? Why (not)? If not, can you think of a way to still sort the results afterwards? Explain this in terms of parallel vs sequential phases of a program.  

* Go to the Deadlock Empire website and complete these two exercises:
    * The Final Stretch: Dragonfire
    * The Final Stretch: Triple Danger