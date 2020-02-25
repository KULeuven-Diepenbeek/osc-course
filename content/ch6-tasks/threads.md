---
title: '6.3: Thread management'
pre: "<i class='fas fa-book'></i> "
weight: 3
draft: true
---

One of the three core tasks of an OS is the **management of tasks**. These different tasks are all running on the same processor. To make this magic happen some form of management is required.

## What's in a thread ?

A process can exist out of multiple **threads**. Up until now all the processes that were discussed contained one thread.

{{% figure src="/img/os/db_singlethreaded.png" title="The single threaded process" %}}
{{% dinobook %}}

Let's examine the image above. On the top of this image the following segments are mentioned: **code**, **data**, and **files**. Additionally the registers and the stack  are mentioned. These registers are the values of the registers that belong to the processor for this process. Such a process is refered to as a **single-threaded process**.

When multiple processes run, every process has **an image** like shown below. This means that multiple instances of the same program have **isolated** code segments, stack, ... . 

{{% figure src="/img/os/db_singlethreaded_twice.png" title="The single threaded process" %}}
{{% dinobook %}}

As can be learned from even looking at the name **multi-threaded** process, such a process has more than a single thread. It could be seen as multiple processes of the same process that share certain aspects. An image says more than a thousand words ... so below is a comparison between a single-threaded process and a multithreaded process.
{{% figure src="/img/os/db_multithreaded.png" title="A single-threaded vs multit-hreaded process" %}}
{{% dinobook %}}



<table style="border: 0px;">
    <tr>
        <td width="50%">
          The multiple threads in a multithreaded process share:
* the code segment
* the data segment
* the list of open files
        </td>
    </tr>
    <tr><td>{{< figure src="https://images.fridaymagazine.ae/1_2244719/imagesList_0/159508486_main.jpg" width="500px" >}}</td>
        <td><h4>Embedded systems</h4>Embedded systems come in many flavours, colours and sizes. Typically, these devices are smaller and have fewer features than the laptops and co do. It goes without saying that the OSes that run on embedded systems are different to, or at least ported from, the other OSes. A number of OSes for embedded systems are: Android, FreeRTOS, Symbian, mbedOS, and brickOS.</td></tr>
</table>


