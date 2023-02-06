---
title: '7.4: Mr. nice guy(lab)'
pre: "<i class='fas fa-vial'></i> "
weight: 4
---

{{<figure src="/img/mrniceguy.jpg" title="image source: amazon.com">}}

* Write a program in C that fetches its own **PID** and **priority**. Display the PID, the nice value and the priority.
    * hint: use `getpriority()` in ```#include <sys/resource.h>``` and use PRIO_PROCESS

{{% figure src="/img/sched/ss_741.png" title="An example output" %}}


<!-- https://www.tecmint.com/set-linux-process-priority-using-nice-and-renice-commands/ -->

* Adjust the program above (after copying it, off course) so it sleeps for 5 seconds after those operations. Repeat that process for 100 times. Compile and run that program. While that program is running, and is reporting back every 5 seconds: 
  * change the nice value (on another terminal. Search on google for the command you need for this.)
  * verify in the reporting that it works
  * change the nice value so the overall priority is at its lowest
  * change the nice value so the overall priority is at its highest

{{% figure src="/img/sched/ss_742.png" title="An example output" %}}

* Adjust the program above (after copying it, off course) so it goes through the exact same changes in priority. Instead of changing it **externally** the program should change it **internally**, on itself.
    * hint: use `setpriority()`

{{% figure src="/img/sched/ss_743.png" title="An example output" %}}

* Write a program in C that forks 25 new processes. Each forked process re-nices itself to one specific value (equally distributed over -20, -10, 0, 10, 19). That re-niced value won't change anymore. After doing that, the processes **count** the number prime numbers lower than 10000. When they are finished, they print their count value (together with their ID and the PRIORITY).
  * Make sure the parent process waits until all its children are done.
  * The printing of the count value is important ... Experiment what happens when you don't do that.

{{% figure src="/img/sched/ss_745.png" title="An example output" %}}

* Use the `top` command to inspect priority and nice values for running tasks on the system
    * What are the PR and NI columns? How do you interpret their values? How do you see which tasks are real-time tasks?
    * Use `top` while running the previous two exercises. Do you see the values changing as you'd expect? Why (not)?

* Adjust the <a href="https://raw.githubusercontent.com/KULeuven-Diepenbeek/osc-course/master/archive_jo/scheduling/blink.c">blink program</a>
    * By default, you can configure this to give all of the processes either high, normal or low priority (see the defines on top)
    * Change the logic so that the first half of the processes (top of the screen) get highest priority, and the bottom half get lowest priority
    * Describe the results. Is this what you expected? Why (not)?
    * Note: since you're running Ubuntu in a Virtual Machine, it might be that it can't handle the default amount of processes. If necessary, lower the count and try again.