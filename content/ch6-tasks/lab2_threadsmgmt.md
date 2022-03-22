---
title: '6.5: Threads (lab)'
pre: "<i class='fas fa-vial'></i>"
weight: 5
---

{{<figure src="/img/os/db_threads.png">}}
{{% dinobook %}}

## Creating and inspecting threads

* Take a closer look at the first pthreads example code from the previous section (with the startThreadJob function).

    * Without executing the code, what do you think will be printed to the screen (with regards to the "Job %d started and Job %d finished" messages)? Why?
    * Compile and run the code on your machine
    * What is the actual output? Is it the same as what you guessed? Why (not)?
    * Now run the second pthreads example code (with the threadWithParameter function). Does it have the same problem? Why (not)?
    * Note: you do not have to think of a "fix" for this problem just yet: we'll discuss some possible solutions in the next Section on inter-thread communication.

* Write a C-program that has 3 threads. Each thread is passed its integer ID (1,2,3) through a parameter and announces its existence through a printf() together with its PID. Note that, unlike when spawning multiple processes, the PID is of course the same for all threads.

    * Note: the second pthreads example code for passing parameters is a bit dirty, requiring an if-test for each thread to pass the correct string parameter. For this exercise, make sure you approach this in a (much) cleaner way!
    * Now change the code so the PID isn't printed in the thread itself, but rather passed as a return value to the main thread (via `pthread_join`) and printed there. 

{{% figure src="/img/os/sc_641.png" title="An example output of the first part of the exercise" %}}

* In the previous processes lab, you had to implement a program that spawned different parallel processes, each calculating all the primes between 0 and a given number. Let's adapt this to threads, but with a twist!

    * Write a C-program that has 4 threads (in addition to the main thread). Each thread calculates all prime numbers between a lower and larger limit. Given a maximum number N which is divisible by 4 (e.g., 100000):
        * Thread 1 computes all primes between 2 and N/4
        * Thread 2 computes all primes between N/4 + 1 and N/2
        * Thread 3 computes all primes between N/2 + 1 and 3N/4
        * Thread 4 computes all primes between 3N/4 + 1 and N
        * Make sure you pass these limits properly to the threads as function parameters. Think about how you can pass more than 1 parameter!

    * **After all threads are done**, the main thread prints all the resulting primes **in the proper order (low to high)** to the screen.
        * Note: this means that the threads don't do the printing themselves like in the previous exercises: you have to instead use heap-allocated memory to communicate back the results to the main thread!
            * For this exercise, it's sufficient for each thread to store their results separately and communicate them back at the end. We will see other options later. 
        * There are several ways of doing this and none of them are perfect (we'll see how to make things better in the next Section). For now, just pick a method you think will work, don't worry *too* much about cleanliness.

    * Imagine you wouldn't have to print the results fully ordered from low to high (but still in the main thread) (You don't actually have to implement this). Would you be able to make the program more efficient then? Why (not)?
        * Put differently: does every thread take an equal amount of time to perform its work. Why (not)?