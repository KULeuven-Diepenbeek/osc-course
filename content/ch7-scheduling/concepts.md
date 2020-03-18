---
title: '7.1: Concepts'
pre: "<i class='fas fa-book'></i> "
weight: 1
draft: true
---

In the previous chapter on Tasks, we've discussed one of the main responsibilities of an operating system: **task management**. Well to be fair, we have only been creating tasks and stopping or killing tasks. The necessary component that allows tasks to be run on the processor is discussed in this chapter: the **scheduler**. For the record, tasks or jobs refer to either processes and/or threads.

The scheduler has two main jobs:

1. Dispatching: switching tasks that are running on the processor
2. Choose the order in which tasks are allowed on the processor

Remember the image below ? The first job is the (interrupting and) dispatching of jobs.
{{% figure src="/img/os/db_processstate.png" title="The different process states and their transitions" %}}
{{% dinobook %}}

For the sake of simplicity it is assumed that the system for which the scheduler works only has a single core. The concepts that are elaborated on also hold for multi-core systems.


## (Don't) Interrupt me !!

When a scheduler has dispatched a job onto the processor, it has two possibilities to determine when the next job is dispatched. 

The easiest way is to just let the task run until it is finished. When it **yields** (to give up/away, to release) the processor, the scheduler can dispatch the next job.

The alternative is to interrupt the running job and tell it to gather its stuff and get out.

In scheduler-lingo, the interruption of a running task is called: **preemption**.

The easy way (with the yielding) is called **non-preemptive** or **cooperative** scheduling. It should not come as a surprise that the alternative way is called **preemptive** scheduling.

{{% notice note %}}
If the scheduler needs to preempt jobs after a certain amount of time (or ticks), it requires hardware assistance. The **timer**, as was discussed in chapter 2, is a fundamental piece of hardware for preemptive scheduling.
{{% /notice %}}


## Scheduler algorithms

### FCFS
A simple algorithm that a scheduler can follow is: **First Come, First served** (FCFS). The order in which the jobs arrive is the same as the order on which the jobs are allowed on the processor.

The image below shows three tasks that arrive very close to each other. The result of the schedulers job is shown in the graph.
{{% figure src="/img/sched/ss_coop_fcfs.png" title="FCFS with cooperative scheduling." %}}

To be able different algorithms there is a need of some sort of metric. When studying schedulers, the following metrics can be used:

* **Throughput:** the number of tasks that are executed over time.
* **Average Job Wait Time (AJWT):** the average time that a job needs to wait before it gets scheduled.
* **Average Job Completion Time (AJCT):** the average time that a job needs to wait before it has finished.
* **CPU efficiency (&#0951;<sub>CPU</sub>):** the percentage that the processor performs usual work. 

Applying the first three metrics on the example above gives the following results:

**Throughput:**

  *  3 jobs over 12 seconds => **0.25 jobs / s**

**AJWT:** 

  * Task 1 arrives at 0 sec and can immediately start running => wait time: 0s
  * Task 2 arrives at 0.1 sec and can after 1s => wait time: 0.9s => 1s
  * Task 3 arrives at 0.2 sec and can after 11s => wait time: 10.8s => 11s
  * AJWT = (0 s + 1 s + 11s)/3 = 12s / 3 = **4s**

**AJCT:** 

  * Task 1 arrives at 0 sec, waits 0s and takes 1s => duration: 1s
  * Task 2 arrives at 0.1 sec, waits 1s and takes 10s => wait time: 11.1s => 11s
  * Task 2 arrives at 0.2 sec, waits 11s and takes 1s => wait time: 12.2s => 12s
  * AJWT = (1 s + 11 s + 12s)/3 = 24s / 3 = **8s**

{{% notice note%}}
For these exercises the decimal portion can be rounded away. It is only used to make a distinction in the order of arrival
{{% /notice%}}

### SJF
A second algorithm is the **Shortest Job First (SJF)**. With this algorithm the scheduler looks at the tasks that are in the *ready* state. The shortest job within this queue is allowed first on the processor.

If the scheduler applies the SJF algorithm on the same example, the occupation of the processor looks like shown below.

{{% figure src="/img/sched/ss_coop_sjf.png" title="SJF with cooperative scheduling." %}}

{{% task %}}
Calculate **the three metrics** for the result of the SJF example, above: Throughput, AJWT, and AJCT.
<br/>
<br/>
<div class="solution" id="q711" style="visibility: hidden">
  <b>Answer:</b><br/>
  <p>
    Throughput = 3 taken / 12 s = 0.25 taken/s <br/>
    AJCT = ( 1 s + 2 s + 12 s ) / 3 = 5 s <br/>
    AJWT = ( 0 s + 1 s + 2 s ) / 3 = 1 s 
  </p>
</div>

<input value="Toggle solution" type="button" style="margin: 0 auto;" onclick="toggleAnswer('q711')"/>
{{% /task %}}


{{% notice note %}}
Both algorithms above (FCFS and SJF) are explained using with non-preemptive/cooperative scheduling.
{{% /notice %}}

## Preemptive scheduling

With preemptive scheduling the scheduler can **halt** a task running on the processor. Let's illustrate this with another example. When a new job comes in, the scheduler stops the currently running job and takes the most recently added job.

{{% figure src="/img/sched/ss_preemt_lcfs.png" title="Preemptive scheduling." %}}

In the example above the following actions are taken:

* @ 0s, there is only one job: T2 => schedule T2
* @ 2s, there are two new jobs (T1 and T3) and one old (T2) => schedule T1 (or T3)
* @ 3s, T1 (or T3) is done; there is one old job (T3 (or T1)) and one even older (T2) => schedule T3 (or T1)
* @ 4s, T3 (or T1) has finished; there is one older (T2) => schedule T2
* @ 12s, T2 has finished; there are no more jobs

In the example above, we sort-of used a Last-Come-First-Served approach.

{{% task %}}
Calculate **the three metrics** for the result of the preemption example, above: Throughput, AJWT, and AJCT.
<br/>
<br/>
<div class="solution" id="q712" style="visibility: hidden">
  <b>Answer:</b>
  <p>
  Throughput = 3 taken / 12 s = 0.25 taken/s <br/>
  AJCT = ( 1 s + 12 s + 2 s ) / 3 = 5 s <br/>
  AJWT = ( 0 s + 0 s + 1 s ) / 3 = 0.33 s 
  </p>
</div>

<input value="Toggle solution" type="button" style="margin: 0 auto;" onclick="toggleAnswer('q712')"/>
{{% /task %}}

### Priority-based scheduling
At this point we could try a **SJF** approach with preemption. Although this a perfectly fine exercise **(wink)**, it is pointed out that *estimating* the duration of a job is not an easy task. The OS could base itself on earlier runs of the program (or similar programs), or on the length of the program, but it remains guesswork.

Another algorithm is priority-based scheduling. If you take a closer look at the example above, more specifically at time 2s, the scheduler has two options: 1) schedule T1, or 2) schedule T3. Priority-base scheduling *could* provide a deterministic answer.


{{% task %}}
Let's assume the priorities as mentioned in the image below. Try to complete the graph with the correct scheduler decision.
<figure>
  <a href="/img/sched/ss_preemt_priority.png" data-featherlight="image"><img src="../../img/sched/ss_preemt_priority.png" id="q713"></a>
  <figcaption><h4>Preemptive scheduling.</h4></figcaption>
</figure>

<input value="Toggle solution" type="button" style="margin: 0 auto;" onclick="toggleAnswer('q713')"/>
{{% /task %}}

As can be seen from the example above, this approach might hold a potential risk: **starvation**. Some jobs with lower priority might not get any processor time. They *starve*. A solution for starvation is **priority aging**. This mechanism allows the priority of a job to increase over time in case of starvation. The actual priority is a function of the original priority and the age of the task.


### Round-Robin scheduling
Round-Robin scheduling is a popular algorithm that allows multiple tasks to **time-share** the processor. Jobs are dispatched to and interrupted from the processor on regular moments. 

The smallest amount of time that a job can stay on the processor is called a **time quantum** or **time slice**. Typically the duration of a time slice is between 10 and 100 ms. All jobs in the ready queue get a time slice in a circular fashion. With the mantra "One image says more than a 1000 words" in mind ... here is an example (with an unrealistic time slice of 1s).

{{% figure src="/img/sched/ss_preemt_rr.png" title="Round Robin scheduling." %}}

{{% task %}}
Calculate **the three metrics** for the result of the preemption example, above: Throughput, AJWT, and AJCT.
<br/>
<br/>
<div class="solution" id="q714" style="visibility: hidden">
  <b>Answer:</b>
  <p>
  Throughput = 3 taken / 12 s = 0.25 taken/s <br/>
  AJCT = ( 10 s + 11 s + 12 s ) / 3 = 11 s <br/>
  AJWT = ( 0 s + 1 s + 2 s ) / 3 = 1 s 
  </p>
</div>

<input value="Toggle solution" type="button" style="margin: 0 auto;" onclick="toggleAnswer('q714')"/>
{{% /task %}}



{{% notice warning %}}
The scheduler does not wait until **a task yields** the CPU, but interrupts its execution after a single time slice. 
This does **NOT** mean that a task **cannot** yield the CPU !!! 
<br/>
<br/>
Another way of putting it is: a job can either run until the time slice has run out (this is when the scheduler interrupts the job) or when the job itself yields the processor.
{{% /notice %}}


## TO ADD

The dispatcher should be as fast as possible, since it is invoked during every
process switch. The time it takes for the dispatcher to stop one process and
start another running is known as the dispatch latency.
