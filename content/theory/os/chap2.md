---
title: '2: Introduction to Operating Systems, using Linux'
---

<!--
&laquo;&nbsp;[Back to Table of Contents](/)<br/>

<hr/>
< !--
&raquo;&nbsp;[Naar de labo opgave](#oef)
-->

## 2.1 What is an OS and Why should we use one ?

In the previous chapter the concept of interrupts was introduced. By using these interrupts it becomes easier to execute multiple tasks on a single processor. However, can you imagine developing a complete office-suite using interrupts ? 

If more tasks come into play, interrupts will not be answer to our question. But guess what the answer could be !! **Operating systems !!!**

The image below shows a classic picture when introducing OSes. The user never talks directly to hardware (or the OS), but always to the software. This plays on every of the four levels.

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

Giving a single, clear definition of what an operating systems is, is no simple jobs. The operating is basicaly a layer of software that is responsible for a number of things. Mainly, but certainly not exclusively, these tasks include:
* direct accessing the hardware;
* hide all the complexity of the computer for the user;
* garanty that different tasks are isolated and protected (form each other);
* ...

Different OSes exist for different computing platforms.
<table style="border: 0px;">
    <tr>
        <td width="50%"><h4>Laptops, desktops, and servers</h4>On laptops, desktops, and servers, the most well known operating systems are used. These include: Microsoft's Windows, Linux, and MAC OS. It goes without saying that there are many more operatin systems for these platforms, but some/many of them are fairly unknown. These might include: DOS, BeOS, BSD, Unix, Solaris, SunOS, ...</td>
        <td><img src="https://3.imimg.com/data3/OP/NK/MY-2971758/laptop-desktop-and-server-trading-service-250x250.jpg" width=500px></td>
    </tr>
    <tr><td><img src="https://images.fridaymagazine.ae/1_2244719/imagesList_0/159508486_main.jpg" width="500px"></td>
        <td><h4>Embedded systems</h4>Embedded systems come in many flavours, colours and sizes. Typically, these are smaller and have fewer features than the laptops and co. It goes without saying that the OSes that run on embedded systems are different, or at least ported. A number of OSes for embedded systems are: Android, FreeRTOS, Symbian, mbedOS, and brickOS.</td></tr>
</table>

{{% ex %}}
Which operating system is the best ?
{{% /ex %}}

## 2.2 Types of operating systems

The image above showed that the OS places itself between general software and hardware. In the most inner depth of an OS resides the kernel. This is the heart of the OS. Depending on the type of the kernel, a typical classification of different OSes is:

1. Monolithic kernel
2. Micro kernel
3. Hybrid kernel

A Monotlithic kernel is a