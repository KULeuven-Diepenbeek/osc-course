---
title: '5.1: Intro to OS using Linux'
pre: "<i class='fas fa-book'></i> "
weight: 1
---

<!--
&laquo;&nbsp;[Back to Table of Contents](/)<br/>

<hr/>
< !--
&raquo;&nbsp;[Naar de labo opgave](#oef)
-->

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
        <td>{{< figure src="https://3.imimg.com/data3/OP/NK/MY-2971758/laptop-desktop-and-server-trading-service-250x250.jpg" width="500px" >}}</td>
    </tr>
    <tr><td>{{< figure src="https://images.fridaymagazine.ae/1_2244719/imagesList_0/159508486_main.jpg" width="500px" >}}</td>
        <td><h4>Embedded systems</h4>Embedded systems come in many flavours, colours and sizes. Typically, these devices are smaller and have fewer features than the laptops and co do. It goes without saying that the OSes that run on embedded systems are different to, or at least ported from, the other OSes. A number of OSes for embedded systems are: Android, FreeRTOS, Symbian, mbedOS, and brickOS.</td></tr>
</table>


{{% task %}}
Which operating system is the best ?
{{% /task %}}

### Types of operating systems

The image above showed that the OS places itself between general software and hardware. In the most inner core of an OS resides the kernel. This is the heart of the OS. Depending on the type of the kernel, a typical classification of OSes can be made

{{< figure src="https://upload.wikimedia.org/wikipedia/commons/d/d0/OS-structure2.svg" title="source: https://en.wikipedia.org/wiki/Monolithic_kernel#/media/File:OS-structure2.svg" >}}

* Monolithic kernel
* Microkernel
* Hybrid kernel

A **Monotlithic kernel** is a kernel that runs the __complete__ operating system in kernel space.
Linux is a example of an OS that uses a Monolithic kernel.

A **Microkernel** is a kernel that runs the __bare minimum__ of software in kernel space.
FreeRTOS is a example of an OS that uses a Monolithic kernel.

A **Hybrid kernel** is a type of kernel that is a combination of the two types above. No surprise there, right ?

In the definition the Microkernel it states that it runs the **bare minimum** of software. Generally this contains the following mechanisms: 

* **task management**: Above it is stated that interrupts (as discussed in the previous chapter) will not scalable and that an OS is required when multiple tasks come into play. The management of these tasks is one of the crucial tasks of an OS
* **inter-process communication**: handles what is says: the communication between different processes. More on processes in the next chapter.
* **address space management**: the is only one (memory-) world. How this world is shared between tasks is dictated by this mechanism.

These three mechanism form the core task of an OS and will be elaborated on in the remainder of this course.

### System calls

The area marked in <span style="background-color: yellow">&nbsp;yellow&nbsp;</span> in the figure above is called the **user mode**. The area marked in <span style="background-color: red; color: white">&nbsp; red &nbsp;</span> in the figure above is called the **kernel mode** or the **privileged mode**. A program in user mode has no direct access to the hardware or to the entire memory space. It is also ran with lower priority on the hardware that programs in kernel mode. 

It is stated above that the user only communicates with *software*. When the user, or the software on the user's behalf, needs something from the more privileged world the border between the user mode and kernel mode needs to be crossed. There are special functions that facilitate this: **System Calls**. A list of all the system calls in a Linux operating system can be found [here](http://asm.sourceforge.net/syscall.html#p31).

## Linux

Linux is a an open source Unix-like OS. Although whole books can be (and probably are) written about definitions such as Unix-like and open source, this is of minor importance in this course. What might be worth pointing out is that Linux is based on the Linux kernel. This kernel was first released in 1991 by the Finn: **Linus Torvalds**. 

The Linux kernel almost never comes on its own but is packaged in a distribution (a.k.a. a distro). Such a distro is the collection of various pieces software of software and the linux kernel. There is a large number of Linux distributions available. Which one to pick was (and probably is) the start of multiple cultural wars. My personal 2-cent opinion is to take into consideration what you want to use it for.

{{< figure src="https://upload.wikimedia.org/wikipedia/commons/1/1b/Linux_Distribution_Timeline.svg" title="source: https://upload.wikimedia.org/wikipedia/commons/1/1b/Linux_Distribution_Timeline.svg" >}}


If the figure above doesn't contain a distribution to your liking you can always DIY it: [Linux from scratch](http://www.linuxfromscratch.org/). Happy compiling !!


One of the aspects in which these distro's differ is the packaging system with which it's distributed. These packaging systems allow you to install/uninstall/... your software. The people that are making distro's take source code from main software packets and compile them using the distro's dependencies. This is then packaged and made available for package managers to install from. Typical examples of package mangers are:

| Name | Extension | Typical distro's |
|---|---|---|
| dpkg | .deb | Debian and Ubuntu a.o.|
| RPM | .rpm | Red Hat, Fedora, and CentOS a.o. |
| packman | .pkg.tar.xz | Arch Linux, FeLi Linux a.o. |

{{% notice note %}}
If you search for Bodhi in the image above, you'll learn that Bodhi is based on Ubuntu, which is based on Debian. Therefore APT (Advanced Package Tool) is used.
{{% /notice %}}

{{% task %}}
1. Use apt to see a list of the installed packages in the VM
2. Update the list of packages in the VM
3. Upgrade all packages to the most recently available version
4. Install **frozen-bubble** in the VM
{{% /task %}}


## Got Root ?
Most operating system allow for multiple users to share one system. Like in most OS-es linux also has an **administrative** user, or super-user: **root**. This privileged user is not to be used when doing day-to-day work. However, you are able to login as a root user and do everything you like as this user. Again: **this is strongly discouraged !!** 

A better way of approaching your day-to-day work on a Linux system is to use a standard user. Whenever you need a higher privilege-level, you can use **sudo**. This is a simple tool that allows regular user to execute certain commands as the root-user. The VM with this course is organised in this way.

{{% figure src="https://imgs.xkcd.com/comics/sandwich.png" title="source: xkcd.com"%}}

Every user that has a login on a Linux system automatically belongs to a **group**. Depending on the distribution, this group can have multiple names. On **Bodhi** a new group is created for every user that bares the same name.

## On files and such
On Linux, almost everything is a file. A file ... is a file. A directory ... is a file. A harddrive ... is a file. A UART port ... is a file. Every file is owned by one user. All other users' privileges are based on the **access permissions**.

{{% figure src="/img/os/accesspermissions.png" title="Access permissions in an example folder"%}}

The image above shows the content of a folder **example** this folder contains: 2 files, 2 directories, a *hidden* directory, and a *hidden* file. With *hidden* is meant that these files are not seen with a normal *ls*. To see these files the **-a** options has to be present.

With the **-l** the *long listing* format is shown (as is seen in the image above). With this, the access permissions are shown in the first 10 characters of each line:
{{% figure src="https://1.bp.blogspot.com/-4YYentw6dEM/W2WjhM1l1DI/AAAAAAAAL6M/2pJn_KbDXmUPEImvikiCFcnWJ0pLvzVVACLcBGAs/s640/UNIX%2Bfile%2Bpermissions%2Bby%2BJulia%2BEvans.jpg" title="source: somewhere on the Internet, found through Google"%}}
