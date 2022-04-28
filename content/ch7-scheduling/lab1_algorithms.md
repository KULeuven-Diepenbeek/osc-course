---
title: '7.2: Scheduling algorithms (lab)'
pre: "<i class='fas fa-vial'></i> "
weight: 2
---

{{<figure src="/img/sched/labs_central.jpg" title="image source: unsplash.com">}}

## Let's compare !

We have discussed a number of algorithms the scheduler can use to do its job. Let's compare them. We assume the following tasks:

* T1: arrives @ 0s, takes 10s, and has priority low
* T2: arrives @ 1s, takes 2s, and has priority high
* T3: arrives @ 4s, takes 5s, and has priority high
* T4: arrives @ 7s, takes 1s, and has priority medium

Compare Average Throughput, AJWT, and AJCT of the 4 algorithms we've seen up until: 

1. cooperative (non preemptive) FCFS, 
2. cooperative (non preemptive) SJF, 
3. preemptive priority based, and 
4. preemptive round robin (with a 1s time slice)

