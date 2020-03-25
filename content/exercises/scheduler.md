---
title: '4. Pseudo scheduler'
pre: "<i class='fas fa-pen-square'></i> "
weight: 4
draft: true
---

{{<figure src="/img/ass4_sched/poepjee.jpg" title="image source: youtube.com">}}

### Scheduler
In this assignment you're going to build a (pseudo) scheduler. A number of tasks will be provided. The scheduler follows the next rules to schedule the presented tasks:

0. The scheduler is preemtive and uses a round-robin approach without priorities.
0. The (virtual) time slice is 1 second.
0. If a new job is announcing itself, it gets a time slice right away.

### Circular Linked List


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

* The **struct** that is to hold the tasks is predefined:

{{< highlight c >}}
// typedefs
typedef struct ST_PCB {
  int arrival_time;
  char name[9];
  int duration;
  struct ST_PCB * next;
} T_PCB;
{{< /highlight >}}

* two functions are provided to show linked lists:

<div class="multicolumn">
  <div class="column">
    <h4>One for linear lists</h4>
{{< highlight c >}}
void show_tasks_lin(T_PCB * head) {
  T_PCB * ptr;
  int ID = 0;

  if(head == NULL ){
    printf("Linear list is empty\n");
  } else {
    ptr = head;
    printf("Printing linear list\n");
    printf("  ID |    TASK  |  duration | arrival time\n");
    printf("  ---+----------+-----------+-----------\n");

    while(ptr != NULL) {
      printf("  %2d | %s | %8d  | %5d\n", ID, ptr->name, ptr->duration, ptr->arrival_time);
      ptr = ptr->next;
      ID++;
    }
    printf("\n");
  }
}
{{< /highlight >}}
  </div>
  <div class="column">
    <h4>One for circular lists</h4>
{{< highlight c >}}
void show_tasks_circ(T_PCB * head) {
  T_PCB * ptr;
  int ID = 0;

  if(head == NULL ){
    printf("Cirulcar list is empty\n");
  } else {

    ptr = head->next;
    while(ptr->next != head){
      ptr = ptr->next;
    }

    printf("Printing circular list\n");
    printf("  ID |    TASK  |  duration | arrival time\n");
    printf("  ---+----------+-----------+-----------\n");

    while(head != ptr) {
      printf("  %2d | %s | %8d  | %5d\n", ID, \
          head->name, head->duration, head->arrival_time);
      head = head->next;
      ID++;
    }
    printf("  %2d | %s | %8d  | %5d\n", ID, \
        head->name, head->duration, head->arrival_time);
    printf("\n");
  }
}
{{< /highlight >}}
  </div>
</div>