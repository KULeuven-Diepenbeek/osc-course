---
title: '6.2: Task management'
pre: "<i class='fas fa-vial'></i> "
weight: 2
---

{{<figure src="/img/os/db_pstree.png">}}
{{% dinobook %}}

## Creating and inspecting processes

* Write a C-program that prints its own PID on the screen.

{{% figure src="/img/os/sc_621.png" title="An example output" %}}

* Write a C-program that spawns another process. Both parent and child processes announce their existence (through a printf) and their PIDs.

{{% figure src="/img/os/sc_622.png" title="An example output" %}}

* Write a C-program that creates 4 child processes
  * every of the childeren checks which numbes (<10k) are [prime](https://en.wikipedia.org/wiki/Prime_number)
  * every child reports only numbers that are prime, together with its own PID

{{% figure src="/img/os/sc_623.png" title="An example output" %}}