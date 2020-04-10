---
title: '4. Pseudo scheduler'
pre: "<i class='fas fa-pen-square'></i> "
weight: 4
---

{{<figure src="/img/ass4_sched/poepjee.jpg" title="image source: youtube.com">}}

### Scheduler
In this assignment you're going to build a (pseudo) scheduler. A number of tasks will be provided. The scheduler follows the next rules to schedule the presented tasks:

0. The scheduler is preemtive and uses a round-robin approach without priorities.
0. The (virtual) time slice is 1 second.
0. If a new job is announcing itself, it gets a time slice right away (last come, first served)


### Circular Linked List
As should be clear from the theory, the (pseudo) scheduler will need to store the incoming. To be consistent with this course and Linux, the run queue is to be implemented using a **linked list**.

The **struct** that is to hold the tasks is predefined:

{{< highlight c >}}
// typedefs
typedef struct ST_PCB {
  int arrival_time;
  char name[9];
  int duration;
  struct ST_PCB * next;
} T_PCB;
{{< /highlight >}}

However in stead of making a linear linked list, as we did earlier; This time you should aim for a circular linked list. This is nothing more than a *normal* linked list where the final element's **next** field points back to the **head** of the list.

{{<figure src="/img/ass4_sched/linear_vs_circular_ll.gif">}}

With this run queue all the tasks are on a merry-go-round (see image above) :smiley:


### Input/output
Both the input and the output are in the form of files.

<div class="multicolumn">
  <div class="column">
    <h4>INPUT</h4>
    {{< highlight bash >}}
3
1
T0000003
6
2
T0000002
3
5
T0000001
4
    {{< /highlight >}}
  </div>
  <div class="column">
    <h4>OUTPUT</h4>
    {{< highlight bash >}}
00 - idle
01 - T0000003 (new)
02 - T0000002 (new)
03 - T0000003
04 - T0000002
05 - T0000001 (new)
06 - T0000003
07 - T0000002
08 - T0000001
09 - T0000003
10 - T0000001
11 - T0000003
12 - T0000001
13 - T0000003
14 - idle
15 - idle
...
    {{< /highlight >}}
  </div>
</div>

<div class="multicolumn">
  <div class="column">
    The <b>input</b> is formatted according to these rules:
    <ol>
      <li>The first line shows the number of tasks that are in the input file</li>
      <li>For each task there are three consecutive lines:
        <ol>
          <li>The arrival time (in seconds)</li>
          <li>Name of the task (<b>exactly 8 characters wide</b>)</li>
          <li>The duration of the task (in seconds)</li>
        </ol>
      </li>
    </ol>
  </div>
  <div class="column">
    The <b>output</b> is formatted according to these rules:
    <ol>
      <li>There is a line for <b>every</b> time slice</li>
      <li>If a task is scheduled it's <b>name</b> is mentioned</li>
      <li>If a new task is scheduled it is indicated with the <b>(new)</b></li>
      <li>If there is no task to scheduled <b>idle</b> is reported</li>
    </ol>
  </div>
</div>

### Some boiler plating

A starting file is provided here. This file provides:

* the definition of the struct
* two functions to show linked lists
{{< highlight c >}}
void show_tasks_lin(T_PCB * head);
void show_tasks_circ(T_PCB * head);
{{< /highlight >}}

* two function that should be completed
{{< highlight c >}}
T_PCB * read_tasks(void);
T_PCB * sort_tasks_on_arrival(T_PCB * head);
{{< /highlight >}}

* a main functions that can only be modified between these lines
{{< highlight c >}}
/* MODIFY BELOW HERE --------------------------------------------------------*/

/* MODIFY ABOVE HERE --------------------------------------------------------*/
{{< /highlight >}}



{{% notice note %}}
The complete boilerplate code is added to the **osc-exercises** repository.
{{% /notice %}}

### Assignment
This assignment requires you to:

* complete the bodies of the two missing functions
* modify the main function **BETWEEN THE INDICATED LINES** so the correct output is produced given a certain input



The resulting C-file is to be uploaded to Toledo.

{{% notice warning %}}
Just, for the record: </br>
  <span style="margin-left: 5%">**Don't create memory leaks !!**</span></br>
  <span style="margin-left: 5%">**Close files that are opened !!**</span></br></br>
**Your solution will be verified with multiple, different input files !!**
{{% /notice %}}
