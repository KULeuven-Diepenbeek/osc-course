---
title: '7.3: Towards real-world schedulers'
pre: "<i class='fas fa-book'></i> "
weight: 3
draft: true
---

The before mentioned algorithms are but a select number from an infinite amount of imaginable algorithms that can be thought of. Off course multiple algorithms can also be combined. The combination of round-robin scheduling with priorities is a combo that is used in many real-world schedulers.

How could be mix both algorithms ? One takes priority into account while the other one does not. The only parameter that can tweaked in Round Robin is the *time slice*. Let's try to figure out how that plays out ... but first ...

{{% figure src="/img/sched/ss_dottedline.png" %}}

Images like the one above, we've seen a number of times up until now. A question that arises is: **<span style="border-bottom: 2px dotted black">what happens on the dotted line ?<span>**

As was mentioned before the scheduler has two main jobs:

0. Choose the next task task that is allowed on the processor
0. Dispatching: switching tasks that are running on the processor

The algorithms provide the scheduler with an approach to **choose the next task**. The second function a scheduler has is the **dispatching** of the newly chosen task. Let's break it down.

## Dispatching

There are 2 user jobs: X and Y. X is running on the processor while Y is in the ready state, waiting for CPU-time. The scheduler decides that X's time is over an it's Y's turn on the processor.

**Step 1**

X has be stopped in such a state that it can continue the next time it is scheduled. Therefore, a *snapshot* has to be made. What is value of the program counter, what are values in the registers, which address is the stack pointer pointing to, ... ? All these values need to be stored. As was discussed [earlier](http://localhost:1313/osc-course/ch6-tasks/processes/#process-control-block) the OS keeps a PCB for every process. This PCB is an object that has fields to store all the required parameters. **The PCB of X needs to be updated** 

**Step 2**
X is removed from the processor. The scheduler switches to kernel mode and has to some work to determine which process is next: Y. Y is placed on the processor.

**Step 3**
Everything that happened to the PCB of X, needs to be done in the opposite direction with the PCB of Y: **the PCB of Y needs to be restored**

**Step 4**
The scheduler switches back to user mode.

The dispatching should be as fast as possible, since it is invoked during every process switch. The time it takes for the dispatcher to stop one process and start another running is known as the **dispatch latency**. This is considered 100% overhead.

The updating (an restoring) of PCB's is referred to as **a context switch**.

## Time slice size
With the knowledge of the dispatch latency, the size of the time slice can re-visited. We assume the following setting:

* there are 10 IO intensive tasks (T1 - T10), these
  0. do calculations for 1 ms
  0. request IO operation from disk
  0. wait 10 ms before the result is fetched
* there is 1 calculation intensive task (T11)
* context switching takes 1 ms
* all tasks are long-running

### The time slice is 10 ms

{{% task %}}
Try to understand the load that is put on the CPU. There is a periodic pattern.


0. Try to **draw** the repeating pattern in this timing diagram
0. How many **context switches** are there ?
0. What is the **efficiency** of the CPU ? (Reminder: CPU efficiency (&#0951;<sub>CPU</sub>): the percentage that the processor performs actual work.) **Tip**: read the title of this section !!

<figure>
  <a href="/img/sched/ss_ts.png" data-featherlight="image"><img src="../../img/sched/ss_ts.png" id="img_q721"></a>
  <figcaption><h4>Time slice = 10 ms</h4></figcaption>
</figure>

<div class="solution" id="div_q721" style="visibility: hidden">
  <b>Answer:</b><br/>
  <p>
    2. There are 11 context switches.<br/>
    3. &#0951;<sub>CPU</sub> = t<sub>useful</sub> / t<sub>total</sub> = 110 ms / 121 ms = 0.90909 <br/>
      <span style="padding-left: 20px">&nbsp;</span>t<sub>useful</sub> = 10 x t<sub>IO</sub> + 1 x t<sub>CPU</sub> = 10 x 10ms + 1 x 10ms = 110ms<br/>
      <span style="padding-left: 20px">&nbsp;</span>t<sub>total</sub>= t<sub>useful</sub> + t<sub>overhead> = 110 ms + 11 x 1 ms = 121 ms<br/>
  </p>
</div>

<input value="Toggle solution" type="button" style="margin: 0 auto;" onclick="toggleAnswer('q721')"/>
{{% /task %}}

### The time slice is 100 ms
{{% task %}}
Try to understand the load that is put on the CPU. There is a periodic pattern.

0. Try to **draw** the repeating pattern in this timing diagram
0. How many **context switches** are there ?
0. What is the **efficiency** of the CPU ? (Reminder: CPU efficiency (&#0951;<sub>CPU</sub>): the percentage that the processor performs actual work.) **Tip**: read the title of this section !!

<figure>
  <a href="/img/sched/ss_ts.png" data-featherlight="image"><img src="../../img/sched/ss_ts_l.png" id="img_q722"></a>
  <figcaption><h4>Time slice = 100 ms</h4></figcaption>
</figure>

<div class="solution" id="div_q722" style="visibility: hidden">
  <b>Answer:</b><br/>
  <p>
    2. There are 11 context switches.<br/>
    3. &#0951;<sub>CPU</sub> = t<sub>useful</sub> / t<sub>total</sub> = 200 ms / 211 ms = 0.94787 <br/>
      <span style="padding-left: 20px">&nbsp;</span>t<sub>useful</sub> = 10 x t<sub>IO</sub> + 1 x t<sub>CPU</sub> = 10 x 10ms + 1 x 100ms = 200ms<br/>
      <span style="padding-left: 20px">&nbsp;</span>t<sub>total</sub>= t<sub>useful</sub> + t<sub>overhead> = 200 ms + 11 x 1 ms = 211 ms<br/>
  </p>
</div>

<input value="Toggle solution" type="button" style="margin: 0 auto;" onclick="toggleAnswer('q722')"/>
{{% /task %}}


### What does it all mean ?

With the examples above, it should be clear that the size of the time quantum has an impact on the CPU efficiency. Be careful, however, that you formulate the correct conclusion. Stating that a larger time slice would **"always"** increases the CPU efficiency is <u>not correct</u>.

Concluding that a system with a lot of IO-intensive tasks is better of with a smaller time slice, and a system with a lot of CPU-intensive tasks is better of with a larger time slice, would be more correct.

For the sake of correctness it is pointed out that the time for context switches is not realistic. With larger time quanta the time for context switching also increases. As a rule of thumb it can be assumed that the time for a context switch is (a little) less than 10% of the time slice.

## Real-life schedulers

### Run queue - Hey, you there, get in line !!!
Processes that are ready to be scheduled are in the **ready** state. Processes that are waiting for IO are in state. All these **queues** need to be maintained and managed. In the chapter on *Pointers*, *linked lists* were discussed. This technique is heavily used for managing these types of queues.

Depending on the strategy that a scheduler follows different queue systems might be more suited. Remember, the scheduler chooses the next task, a preferably as-fast-as-possible.

#### A simple run queue
The simplest type of a run queue would be a FIFO (first-in-first-out). It should be clear that a scheduler that uses a first-come-first-serve algorithm finds a perfect match with this type of run queue.

**When a process is created**, it is simply added to the back of the queue.

{{% figure src="/img/sched/ss_runqueue_fifo.png" %}}

#### Multiple FIFOs
A priority based system might use the exact same scheduling algorithm, with the exception of priorities. A solution could be to use multiple FIFOs: one FIFO for each priority level.

**When a process is created**, it is simply added to the back of the queue that matches the process's priority level.

{{% figure src="/img/sched/ss_runqueue_multfifo.png" %}}

#### Tree
When a more complex algorithms are used in the scheduler, a tree might suit the needs better. Depending on the strategy a tree might be ordered in a certain way. For example, in a **shortest-job-first** algorithm, jobs may be ordered (from **short** to **long**) in the tree from **left** to **right**.

**When a process is created**, calculations have to be done to determine the position in the three of the new process.

{{% figure src="/img/sched/ss_runqueue_tree.png" %}}

### Multi-level feedback queue
The multi-level feedback queue scheduler was originally develop by Fernando J. Corbató et al. in 1962. It consists of 3 queues. Every queue has a different time slice assigned to it: 8 ms, 16 ms and &#8734; ms.

{{% figure src="/img/sched/ss_mlfq.png" %}}

When a newly created process is added to the scheduler, it arrives in the **shortest queue**. After a number of times being scheduled on the processor, the process might **go down** a level to a queue with a larger time slice. The criterion that is used is whether the job **yielded** from the processor, or whether it was interrupted by the scheduler.

Jobs that always use up the complete time slice are considered to be more CPU intensive. As we have seen earlier, this type of process is more efficient when given a larger time slice. The scheduler moves the process to lower level. The **reverse** holds for moving up in between queues.

With this scheduler, jobs might migrate between queues over time depending on what time slice is best suited for that moment. In general it can be stated that CPU intensive processes are to be found on the bottom, while IO intensive processes are on the top.

### Linux Scheduler
The Linux kernel has used different schedulers up until now. Between Linux kernels 2.4 - 2.6 were using the O(n) scheduler, 2.6 - 2.6.11 the used scheduler was O(n), and from 2.6.12 onward the Completely Fair Scheduler (CFS) was used. These schedulers are briefly touched upon here. All of these are preemptive schedulers that are priority-based. 

#### O(n) scheduler
The O(n) (read as: [Big-Oh-En]) scheduler got his name from the fact that choosing a new task had **linear** complexity. This means that the amount it takes for choosing a new task is proportional the number of tasks that are available. As you can easily see on every OS, there are a huge amount of tasks running nowadays. With this scheduler it would also take a (relatively) huge amount of time for choosing the next task. **This doesn't scale !** Because the scheduler's work is seen as overhead, it should be clear why this scheduler got replaced.

#### O(1) scheduler
This scheduler has been used in the Linux kernel up to version 2.6.23. This scheduler picks the next task in O(1), constant time. Obviously, this scales better. While this scheduler fixed the scalability problem of its predecessor, it did not perform well with an increasing number of **interactive processes**.

#### CFS scheduler (currently used)


There are 140 different priority levels in the O(1) scheduler. Processes are divided in 2 types: Real-time processes and timesharing processes. The **real-time** processes are those with a priority from 0 to 99. The **timesharing** processes have priority from 100 to 139.

When a 
The Linux scheduler is a preemptive, priority-based algorithm with two
separate priority ranges: a real-time range from 0 to 99 and a nice value
ranging from −20 to 19. Smaller nice values indicate higher priorities. Thus,
by increasing the nice value, you are decreasing your priority and being “nice”
to the rest of the system.

CFS is a significant departure from the traditional UNIX process scheduler.
In the latter, the core variables in the scheduling algorithm are priority and
time slice.  Traditional UNIX systems give processes a fixed
time slice, perhaps with a boost or penalty for high- or low-priority processes,
respectively. A process may run for the length of its time slice, and higherpriority processes run before lower-priority processes. It is a simple algorithm
that many non-UNIX systems employ. Such simplicity worked well for early
time-sharing systems but has proved incapable of delivering good interactive
performance and fairness on today’s modern desktops and mobile devices.
CFS introduced a new scheduling algorithm called fair scheduling that
eliminates time slices in the traditional sense. 

Instead of time slices, all processes
are allotted a proportion of the processor’s time. CFS calculates how long a
process should run as a function of the total number of runnable processes.

To start, CFS says that if there are N runnable processes, then each should be afforded 1/N of the processor’s time. CFS then adjusts this allotment by weighting each process’s allotment by its nice value. Processes with the default nice value have a weight of 1—their priority is unchanged. Processes with a smaller nice value (higher priority) receive a higher weight, while processes
with a larger nice value (lower priority) receive a lower weight. CFS then runs
each process for a “time slice” proportional to the process’s weight divided by
the total weight of all runnable processes.
To calculate the actual length of time a process runs, CFS relies on a
configurable variable called target latency, which is the interval of time during
which every runnable task should run at least once. For example, assume
that the target latency is 10 milliseconds. Further assume that we have two
runnable processes of the same priority. Each of these processes has the same
weight and therefore receives the same proportion of the processor’s time. In
this case, with a target latency of 10 milliseconds, the first process runs for
5 milliseconds, then the other process runs for 5 milliseconds, then the first
process runs for 5 milliseconds again, and so forth. If we have 10 runnable
processes, then CFS will run each for a millisecond before repeating.
But what if we had, say, 1, 000 processes? Each process would run for 1
microsecond if we followed the procedure just described. Due to switching
costs, scheduling processes for such short lengths of time is inefficient.
CFS consequently relies on a second configurable variable, the minimum
granularity, which is a minimum length of time any process is allotted the
processor. All processes, regardless of the target latency, will run for at least the
minimum granularity. In this manner, CFS ensures that switching costs do not
grow unacceptably large when the number of runnable processes grows too
large. In doing so, it violates its attempts at fairness. In the usual case, however,
the number of runnable processes remains reasonable, and both fairness and
switching costs are maximized.
With the switch to fair scheduling, CFS behaves differently from traditional
UNIX process schedulers in several ways. Most notably, as we have seen, CFS
eliminates the concept of a static time slice. Instead, each process receives
a proportion of the processor’s time. How long that allotment is depends on
how many other processes are runnable. This approach solves several problems
in mapping priorities to time slices inherent in preemptive, priority-based
scheduling algorithms. It is possible, of course, to solve these problems in other
ways without abandoning the classic UNIX scheduler. CFS, however, solves the
problems with a simple algorithm that performs well on interactive workloads
such as mobile devices without compromising throughput performance on the
largest of servers.




### Other schedulers
As might be expected, these are not the only schedulers that exist. There a many scheduler available and, certainly, there will be many more to come. Just a small grasp of existing schedulers: 

* Completely Fair Scheduler (Linux)
* Brain F\*ck Scheduler (Linux)
* Noop Scheduler (Linux)
* Task Scheduler 1.0 (Windows)
* Task Scheduler 2.0 (Windows)
* JobScheduler (iOS)