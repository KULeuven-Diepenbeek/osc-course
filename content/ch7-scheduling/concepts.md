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
Calculate **the three metrics** for the this result: Throughput, AJWT, and AJCT.

The answer is written below this "Exercise !" However the font is white-on-white. Select the text, or open the page-source to verify your answer.
{{% /task %}}

















<div style="border: 1px solid black">
  <div><b>Answer:</b></div>
  <div style="color: white; border: 3px solid '#01407a'; padding-left: 20px; ">
  Throughput = 3 taken / 12 s = 0.25 taken/s <br/>
  AJCT = ( 1 s + 2 s + 12 s ) / 3 = 5 s <br/>
  AJWT = ( 0 s + 1 s + 2 s ) / 3 = 1 s 
  </div>
</div>


The dispatcher should be as fast as possible, since it is invoked during every
process switch. The time it takes for the dispatcher to stop one process and
start another running is known as the dispatch latency.
