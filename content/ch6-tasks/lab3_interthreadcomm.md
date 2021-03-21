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

* Let's revisit the prime numbers for one last time. Like the prime-exercise in the previous lab, we will have 4 separate threads, each calculating a subsection of primes between 2 and N. Now however, we will use a single, shared memory structure, instead of having each thread storing their full results in separate memory. Each prime-calculting thread thus communicates each discovered prime **as soon as possible** back to a single processing entity. This can be accomplished in several different ways:

    * You can have 1 big array and a counter (indicating how many items are in the array) and lock both using a Mutex
        * Extra points if you can think of a way to not make this array take up excessive memory by the time the calculations are done
    * You can view the prime-threads as producers and have a separate consumer thread that reads primes as they are produced and puts them in the results array (using Semaphores to signal)
        * Note that depending on your approach, this might still require a little bit of thread-local memory too of course (why? think about it!), but much less than previously
    * Instead of an array + counter, you could use a linked list for both setups

    * The goal is to implement **one** of these options (you choose), think deeply about the rest, and then answer the following questions:
        * Which approach should be faster: this one with shared memory or the one from the previous lab using per-thread memory?
        * Which tradeoffs were made here in comparison with the previous version? (e.g., faster but less flexible, slower but less memory, ...)
        * Are you able to keep the primes sorted in this new version? Why (not)? If not, can you think of a way to still sort the results afterwards? Explain this in terms of parallel vs sequential phases of a program.  


* Go to the Deadlock Empire website and complete these two exercises:
    * The Final Stretch: Dragonfire
    * The Final Stretch: Triple Danger