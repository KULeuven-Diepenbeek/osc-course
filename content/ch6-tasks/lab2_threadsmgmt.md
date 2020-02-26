---
title: '6.4: Threads'
pre: "<i class='fas fa-vial'></i> "
weight: 4
---

{{<figure src="/img/os/db_threads.png">}}
{{% dinobook %}}

## Creating and inspecting threads

* Write a C-program that has 3 threads. Each threads announces its existence (through a printf) and their PIDs.

* Write a C-program that creates 4 threads
  * every of the threads checks which numbes (<10k) are [prime](https://en.wikipedia.org/wiki/Prime_number)
  * every child reports only numbers that are prime, together with its own PID
