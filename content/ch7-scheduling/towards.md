---
title: '7.3: Towards real-world schedulers'
pre: "<i class='fas fa-book'></i> "
weight: 3
---

The before mentioned algorithms are but a select number from an infinite amount of imaginable algorithms that can be thought of. Off course multiple algorithms can also be combined. The combination of round-robin scheduling with priorities is a combo that is used in many real-world schedulers.

How could we mix both algorithms ? One takes priority into account while the other one does not. The only parameter that can tweaked in Round Robin is the *time slice*. Let's try to figure out how that plays out ... but first ...

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

## Real-world schedulers

### Run queue - Hey, you there, get in line !!!
Processes that are ready to be scheduled are in the **ready** state. Processes that are waiting for IO are in **waiting** state. All these **queues** need to be maintained and managed. In the chapter on *Pointers*, *linked lists* were discussed. This technique is heavily used for managing these types of queues.

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
The Linux kernel has used different schedulers up until now. Between Linux kernels 2.4 - 2.6 were using the O(n) scheduler, 2.6 - 2.6.11 the used scheduler was O(1), and from 2.6.12 onward the Completely Fair Scheduler (CFS) was used. These schedulers are briefly touched upon here. All of these are preemptive schedulers that are priority-based. 

#### O(n) scheduler
The O(n) (read as: [Big-Oh-En]) scheduler got his name from the fact that choosing a new task had **linear** complexity. This means that the amount it takes for choosing a new task is proportional the number of tasks that are available. As you can easily see on every OS, there are a huge amount of tasks running nowadays. With this scheduler it would also take a (relatively) huge amount of time for choosing the next task. **This doesn't scale !** Because the scheduler's work is seen as overhead, it should be clear why this scheduler got replaced.

#### O(1) scheduler
This scheduler has been used in the Linux kernel up to version 2.6.23. This scheduler picks the next task in O(1), constant time. Obviously, this scales better. While this scheduler fixed the scalability problem of its predecessor, it did not perform well with an increasing number of **interactive processes**.

#### CFS (currently used)
The currently used scheduler has been around since Linux kernel version 2.6.23. As it is more fair towards interactive processes, or more in general, more fair towards all processes, it is named: Completely Fair Scheduler (CFS).

There are 140 different priority levels in the CFS. Processes are divided in 2 types: Real-time processes and time sharing processes. The **real-time** processes are those with a priority from 0 to 99. The **time sharing** processes have a priority from 100 to 139. The real-time processes are processes that run in kernel mode, the time sharing processes run in user mode.

As was seen in the example above, it helps when processes don't have a fixed priority. Additionally, the concept of priority ageing was discussed as means to counteract starvation. A priority should be able to **change throughout the process's lifetime**. This is implemented with the **nice value**. This value is added to the original priority and ranges between -20 and 19. Smaller nice values give higher priorities. Larger nice values (*nicer processes*) give lower priorities.

For more information on CFS you can read the kernel documentation [here](https://www.kernel.org/doc/html/latest/scheduler/sched-design-CFS.html). For the daredevils ... you can even read (or modify, at your own risk) the kernel C code [here](https://github.com/torvalds/linux/blob/master/kernel/sched/fair.c).

{{% task %}}
What should be the default priority that is given to a user process ?
{{% /task %}}

{{% notice note %}}
When a process is **nicer** to other processes, it has a higher nice value. Therefore the overall priority of nicer processes is lower, which is reflected by a **higher** overall priority.  
{{% /notice %}}

The clip below tries to illustrate the effect of the overall priority.
{{< youtube Bt-Z_Y5Zl44 >}}

Although there are **more differences** with earlier scheduler, albeit not so drastically, a thorough study on this algorithm falls out of the scope of this course. In summary, CFS eliminates the concept of a static time slice. This approach solves several problems in mapping priorities to time slices. CFS solves the problems with a simple algorithm that performs well on interactive workloads such as mobile devices without compromising throughput performance on the largest of servers.


### Other schedulers
As might be expected, these are not the only schedulers that exist. There a many scheduler available and, certainly, there will be many more to come. Just a small grasp of existing schedulers: 

* Completely Fair Scheduler (Linux)
* Brain F\*ck Scheduler (Linux)
* Noop Scheduler (Linux)
* Task Scheduler 1.0 (Windows)
* Task Scheduler 2.0 (Windows)
* JobScheduler (iOS)