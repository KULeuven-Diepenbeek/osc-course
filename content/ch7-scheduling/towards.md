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
<!-- {{% figure src="/img/sched/ss_ts10ms.png" %}} -->

### What does it all mean ?

With the examples above, it should be clear that the size of the time quantum has an impact on the CPU efficiency. Be careful, however, that you formulate the correct conclusion. Stating that a larger time slice would **"always"** increases the CPU efficiency is <u>not correct</u>.

Concluding that a system with a lot of IO-intensive tasks is better of with a smaller time slice, and a system with a lot of CPU-intensive tasks is better of with a larger time slice, would be more correct.



For the sake of correctness it is pointed out that the time for context switches is not realistic. With larger time quanta the time for context switching also increases. As a rule of thumb it can be assumed that the time for a context switch is (a little) less than 10% of the time slice.