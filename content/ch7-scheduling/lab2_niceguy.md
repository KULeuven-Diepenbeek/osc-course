---
title: '7.4: Mr. nice guy(lab)'
pre: "<i class='fas fa-vial'></i> "
weight: 4
---

{{<figure src="https://images-na.ssl-images-amazon.com/images/I/41mzOaXP%2BcL._SX337_BO1,204,203,200_.jpg" title="image source: amazon.com">}}

* Write a program in C that fetches its own **PID** and **priority**. Display the PID, the nice value and the priority.

{{% figure src="/img/sched/ss_741.png" title="An example output" %}}

* Adjust the program above (after copying it, off course) so it sleeps for 5 seconds after those operations. Repeat that process for 100 times. Compile and run that program. While that program is running, and is reporting back every 5 seconds: 
  * change the nice value (on another terminal)
  * verify in the reporting that it works
  * change the nice value so the overall priority is at its lowest
  * change the nice value so the overall priority is at its highest

{{% figure src="/img/sched/ss_742.png" title="An example output" %}}

* Adjust the program above (after copying it, off course) so it goes through the exact same changes in priority. Instead of changing it **externally** the program should change it **internally**, on itself.

{{% figure src="/img/sched/ss_743.png" title="An example output" %}}

* Find the Linux kernel version on the CLI.

{{% figure src="/img/sched/ss_744.png" title="An example output" %}}

* Write a program in C that forks 25 new processes. Each forked process re-nices itself to one specific value (equally distributed over -20, -10, 0, 10, 19). That re-niced value won't change anymore. After doing that, the processes **count** the number prime numbers lower than 10'000. When they are finished they print their count value (together with their ID and the PRIORITY).
  * Make sure the parent process waits until all its children are done.
  * The printing of the count value is important ... Experiment what happens when you don't do that.

{{% figure src="/img/sched/ss_745.png" title="An example output" %}}