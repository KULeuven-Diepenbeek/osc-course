---
title: '4. Pseudo scheduler'
pre: "<i class='fas fa-pen-square'></i> "
weight: 4
---

{{<figure src="/img/ass4_sched/poepjee.jpg" title="image source: youtube.com">}}

### Scheduler

In this assignment you're going to build a (pseudo) scheduler. A number of to-be-scheduled tasks will be provided via an input file. 

The scheduler follows these rules:

0. The scheduler is preemptive and uses a round-robin approach without priorities.
0. The (virtual) time slice is 1 second.
0. There is no (measurable) context switching overhead.
0. If a new job arrives in the queue, it gets a time slice right away (last-come, first-served)


### Circular Linked List

As should be clear from the theory, the (pseudo) scheduler will need to store the incoming tasks. To be consistent with this course and Linux, the run queue is to be implemented using a **linked list**.

The **struct** that is to hold the tasks is predefined:

{{< highlight c >}}
typedef struct ST_PCB {
  int arrival_time;
  char name[9];
  int duration;
  struct ST_PCB * next;
} T_PCB;
{{< /highlight >}}

However, instead of using just a linear linked list (as we did earlier), this time you should aim for using a **circular linked list** as well. This is nothing more than a *normal* linked list where the final element's **next** field points back to the **head** of the list.

{{<figure src="/img/ass4_sched/linear_vs_circular_ll.gif">}}

With this run queue all the tasks are on a merry-go-round (see image above) :smiley:, which makes it easier to keep scheduling them until they are all done. 


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
(...)
49 - idle
    {{< /highlight >}}
  </div>
</div>

<div class="multicolumn">
  <div class="column">
    The <b>input</b> file is always named "tasks.txt", and is a normal text file. You can assume that this file is positioned next to the executable. <br/><br/>
    The <b>input</b> is formatted according to these rules:
    <ol>
      <li>The first line shows the number of tasks that are in the input file</li>
      <li>For each task there are three consecutive lines:
        <ol>
          <li>The arrival time (integer > 0, in seconds)</li>
          <li>Name of the task (<b>exactly 8 characters wide</b>)</li>
          <li>The duration of the task (integer > 0, in seconds)</li>
        </ol>
      </li>
    </ol>
  </div>
  <div class="column">
    The <b>output</b> file is always named "output.txt", and is a normal text file. You must write this file in the current working directory (which will be next to the executable). <br/><br/>
    The <b>output</b> MUST be formatted according to these rules:
    <ol>
      <li>Each line starts with a line number of <b>exactly</b> two digits</li>
      <li>There is a line for <b>every</b> time slice</li>
      <li>If a task is scheduled, its <b>name</b> is mentioned</li>
      <li>If a new task is scheduled, it is indicated with <b>(new)</b></li>
      <li>If there is no task to scheduled, <b>idle</b> is reported</li>
      <li>Each line ends with \n (NOT with \r\n) and there are NO spaces between the last character of the line and the \n</li>
      <li>The output reflects the first 50 time slices of a run of the scheduler (so there are 51 lines in each output file, 1 empty at the end)</li>
    </ol>
  </div>
</div>

You MUST strictly follow these formats and filenames, as your code wil be (partially) validated with automated scripts.
If you do not follow these formats and we have to make manual adjustments to your output, points will be deducted.
Test this by directly comparing your output for the test example with the example output: they have to be a perfect match.

### Some boiler plating

A starting file is provided below. This file provides:

* the definition of the ST_PCB struct. You MUST NOT change anything in this struct.
* two functions to show linked lists (to aid in debugging)
{{< highlight c >}}
void show_tasks_lin(T_PCB * head);
void show_tasks_circ(T_PCB * head);
{{< /highlight >}}

* two functions that should be completed
{{< highlight c >}}
T_PCB * read_tasks(void);
T_PCB * sort_tasks_on_arrival(T_PCB * head); // you cannot assume the tasks in the file are in the order they arrive!
{{< /highlight >}}

* a main function that should only be modified between these two lines. You MUST make use of all already defined variables!
{{< highlight c >}}
/* MODIFY BELOW HERE --------------------------------------------------------*/

/* MODIFY ABOVE HERE --------------------------------------------------------*/
{{< /highlight >}}

* Tip: for reading input from a file, use the scanf-family of functions (fscanf, sscanf, ...)
* Tip: when reading names/handling strings, take into account the '\0' character and double-check how c-functions like strlen() use this!
    * if you see weird characters in your output, this is probably the cause

* Tip: for sorting the tasks, use a simple insertion-sort or selection-sort algorithm. 
    * Make sure you don't do unnecessary string copies when sorting the data!

* Note: input can have tasks with overlapping arrival times. For example, tasks 3 and 4 can both arrive at time 10, while 5 arrives at time 11. 
    * In this case, you should aim for a STRICT last-come, first-served approach
    * task 4 should be scheduled at time quantum 10
    * task 5 should be scheduled at time quantum 11
    * task 3 should be scheduled at time quantum 12 (even though it "arrived first")

{{% notice note %}}
The complete boilerplate code and an example tasks.txt and output.txt is added to the **osc-exercises** repository (see <a href="https://github.com/KULeuven-Diepenbeek/osc-exercises/tree/master/assignments">here</a>).
{{% /notice %}}

### Assignment

This assignment requires you to:

* complete the bodies of the two missing functions
* modify the main function **BETWEEN THE INDICATED LINES** so the correct output is produced given a certain input

The resulting C-file is to be uploaded to Toledo.

**Note that, like all other tasks, this is an individual assignment!**

{{% notice warning %}}
Just, for the record: </br>
  <span style="margin-left: 5%">**Don't create memory leaks !!**</span></br>
  <span style="margin-left: 5%">**Close files that are opened !!**</span></br>
  <span style="margin-left: 5%">**Validate for unexpected input !!** (at least a bit)</span></br></br>
**Your solution will be verified with multiple, different input files !!**
{{% /notice %}}
