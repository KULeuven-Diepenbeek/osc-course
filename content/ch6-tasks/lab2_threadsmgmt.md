---
title: '6.5: Threads (lab)'
pre: "<i class='fas fa-vial'></i>"
weight: 5
---

{{<figure src="/img/os/db_threads.png">}}
{{% dinobook %}}

## Creating and inspecting threads

* Write a C-program that has 3 threads. Each thread announces its existence through a printf() together with its PID. Note that, unlike when spawning multiple processes, the PID is of course the same for all threads.

{{% figure src="/img/os/sc_641.png" title="An example output" %}}

* Take a closer look at the Pthreads example code from the previous section (with the doSomeThing function).

    * Without executing the code, what do you think will be printed to the screen (with regards to the "Job started and finished" messages)? Why?
    * Compile and run the code on your machine
    * What is the actual output? Is it the same as what you guessed? Why (not)?
    * Note: you do not have to think of a "fix" for this problem just yet: we'll discuss some possible solutions in the next Section.

* In the processes lab, you had to implement a program that spawned different parallel processes, each calculating all the primes between 0 and a given number. Let's adapt this to threads, but with a twist.

    * Write a C-program that has 4 threads (in addition to the main thread). Each thread calculates all prime numbers between a lower and larger limit. Given a maximum number N which is divisible by 4 (e.g., 100000):
        * Thread 1 computes all primes between 2 and N/4
        * Thread 2 computes all primes between N/4 + 1 and N/2
        * Thread 3 computes all primes between N/2 + 1 and 3N/4
        * Thread 4 computes all primes between 3N/4 + 1 and N
    * After all threads are done, the main thread prints all the resulting primes **in the proper order (low to high)** to the screen.
        * Note: this means that the threads dont print the primes themselves like in the processes exercise: you have to instead use heap-allocated memory to communicate back the results to the main thread!
            * For this exercise, it's sufficient for each thread to store their results separately and communicate them back at the end. We will see other options later. 
        * There are several ways of doing this and none of them are perfect (we'll see how to make things better in the next Section). For now, just pick a method you think will work, don't worry too much about cleanliness.
    * Imagine you wouldn't have to print the results fully ordered from low to high (but still in the main thread) (You don't actually have to implement this). Would you be able to make the program more efficient then? Why (not)?