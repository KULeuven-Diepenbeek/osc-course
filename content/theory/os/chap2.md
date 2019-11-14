---
title: 'Chapter 2: Introduction to Operating Systems, using Linux'
---

<!--
&laquo;&nbsp;[Back to Table of Contents](/)<br/>

<hr/>
< !--
&raquo;&nbsp;[Naar de labo opgave](#oef)
-->

## 2.1 What is an OS and Why should we use one ?

In the previous chapter the concept of interrupts was introduced. By using these interrupts it becomes easier to execute multiple tasks on a single processor. However, can you imagine developing a complete office-suite using interrupts ? 

If more tasks come into play, interrupts will not be the answer to our question. But guess what the answer could be: **Operating systems !!!**

The image below shows the classic picture when introducing OSes. The user **never** talks directly to hardware (or the OS), but always to the software. This protocol holds for all four levels.

{{<mermaid>}}
graph TD
    A[User]
    B[Software]
    C[Operating System]
    D[Hardware]
    
    A --> B
    B --> A
    B --> C
    C --> B
    C --> D
    D --> C
{{< /mermaid >}}

Giving a single, clear definition of what an operating systems is, is no simple job. The operating is basicaly a layer of software that is responsible for a number of things. Mainly, but certainly not exclusively, these tasks include:

* direct accessing the hardware;
* hide all the complexity of the computer for the user;
* garanty that different tasks are isolated and protected (form each other);
* ...

Different OSes exist for different computing platforms.
<table style="border: 0px;">
    <tr>
        <td width="50%"><h4>Laptops, desktops, and servers</h4>On laptops, desktops, and servers, the most well known operating systems are used. These include: Microsoft's Windows, Linux, and MAC OS. It goes without saying that there are many more operating systems for these platforms, but some/many of them are fairly unknown. These might include: DOS, BeOS, BSD, Unix, Solaris, SunOS, ...</td>
        <td><img src="https://3.imimg.com/data3/OP/NK/MY-2971758/laptop-desktop-and-server-trading-service-250x250.jpg" width=500px></td>
    </tr>
    <tr><td><img src="https://images.fridaymagazine.ae/1_2244719/imagesList_0/159508486_main.jpg" width="500px"></td>
        <td><h4>Embedded systems</h4>Embedded systems come in many flavours, colours and sizes. Typically, these devices are smaller and have fewer features than the laptops and co do. It goes without saying that the OSes that run on embedded systems are different to, or at least ported from, the other OSes. A number of OSes for embedded systems are: Android, FreeRTOS, Symbian, mbedOS, and brickOS.</td></tr>
</table>

<div style="background-color: #F00; color: yellow; font-weight: bold; text-align: center">TODO: Uniformly style the polls ?</div>
{{% ex %}}
Which operating system is the best ?
{{% /ex %}}

## 2.2 Types of operating systems

The image above showed that the OS places itself between general software and hardware. In the most inner core of an OS resides the kernel. This is the heart of the OS. Depending on the type of the kernel, a typical classification of OSes can be made
<img src="https://upload.wikimedia.org/wikipedia/commons/d/d0/OS-structure2.svg">
<div class="footnote">source: https://en.wikipedia.org/wiki/Monolithic_kernel#/media/File:OS-structure2.svg</div>

* Monolithic kernel
* Microkernel
* Hybrid kernel

A **Monotlithic kernel** is a kernel that runs the __complete__ operating system in kernel space.
<!--Linux is a example of an OS that uses a Monolithic kernel.-->

A **Microkernel** is a kernel that runs the __bare minimum__ of software in kernel space.

A **Hybrid kernel** is a type of kernel that is a combination of the two types above. No surprise there, right ?

In the definition the Microkernel it states that it runs the **bare minimum** of software. Generally this contains the following mechanisms: 

* **task management**: Above it is stated that interrupts (as discussed in the previous chapter) will not scalable and that an OS is required when multiple tasks come into play. The management of these tasks is one of the crucial tasks of an OS
* **inter-process communication**: handles what is says: the communication between different processes. More on processes in the next chapter.
* **address space management**: the is only one (memory-) world. How this world is shared between tasks is dictated by this mechanism.

These three mechanism form the core task of an OS an will be elaborated on in the remainder of this course.

