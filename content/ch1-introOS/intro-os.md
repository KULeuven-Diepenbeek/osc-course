---
title: '1.1: Intro to OS using Linux'
pre: "<i class='fas fa-book'></i> "
weight: 1
---

TODO intro tekst aanpassen

In Chapter X the concept of interrupts was introduced. By using these interrupts it becomes easier to execute multiple independent tasks on a single processor. However, can you imagine developing a complete office-suite using interrupts?  

When more tasks come into play, interrupts will not be the answer to our question. But guess what the answer could be: **Operating systems !!!** (OSes)

The image below shows the classic picture when introducing OSes. The user **never** talks directly to hardware (or the OS), but always to the software.

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

Giving a single, clear definition of what an operating system is, is no simple job. The OS is basicaly a layer of software that is responsible for a number of things. Mainly, but certainly not exclusively, these tasks include:

* Allowing separate independent programs to use the hardware (ideally at the same time);
* Directly accessing the hardware;
* Hiding most of the complexity of the computer for the user;
* Guaranteeing that different tasks are isolated and protected (from each other);
* ...

One could say an OS is **an abstraction layer** that makes it easier to write software that interfaces with different types of hardware and that ensures a measure of robustness and security. 


Different OSes exist for different computing platforms.
<table style="border: 0px;">
    <tr>
        <td width="50%"><h4>Laptops, desktops, and servers</h4>On laptops, desktops, and servers, the most well known operating systems are used. These include: Microsoft's Windows, Linux, and MAC OS. It goes without saying that there are many more operating systems for these platforms, but some/many of them are fairly unknown to the wider public. These might include: DOS, BeOS, BSD, Unix, Solaris, SunOS, ...</td>
        <td>{{< figure src="https://3.imimg.com/data3/OP/NK/MY-2971758/laptop-desktop-and-server-trading-service-250x250.jpg" width="500px" title="Source: imimg.com" >}}</td>
    </tr>
    <tr><td>{{< figure src="https://images.fridaymagazine.ae/1_2244719/imagesList_0/159508486_main.jpg" width="500px" title="Source: fridaymagazine.ae" >}}</td>
        <td><h4>Embedded systems</h4>Embedded systems come in many flavours, colours and sizes. Typically, these devices are smaller and have fewer features than the laptops and co do. It goes without saying that the OSes that run on embedded systems are different to, or at least ported from, the other OSes. A number of OSes for embedded systems are: Android, FreeRTOS, Symbian, mbedOS, and brickOS.</td></tr>
</table>

In recent years, the distinction between these types of OSes has started to fade, with systems like Android and iOS becoming more full-featured, and even low cost hardware systems like Raspberry PIs being able to run a full Linux OS.

{{% task %}}
Which operating system is the best ?
{{% /task %}}

### Types of operating systems

The image above showed that the OS places itself between general software and hardware. In the most inner core of an OS resides the kernel, the heart of the OS. Depending on the type of the kernel, a typical classification of OSes can be made:

{{< figure src="https://upload.wikimedia.org/wikipedia/commons/d/d0/OS-structure2.svg" title="source: Wikipedia. (IPC: Inter-Process communication. VFS: Virtual Filesystem Switch)" >}}

* A **Monotlithic kernel** is a kernel that runs the __complete__ OS in kernel space.
    Linux is a example of an OS that uses a Monolithic kernel.

* A **Microkernel** is a kernel that runs the __bare minimum__ of an OS in kernel space.
    FreeRTOS is a example of an OS that uses a Microkernel.

* A **Hybrid kernel** is a type of kernel that is a combination of the two types above. No surprise there, right?
    Windows 10 is an example of an OS that uses a Hybrid kernel

In the definition the Microkernel it states that it runs the **bare minimum** of software. Generally this contains the following mechanisms: 

* **Task management**: the ability to run multiple programs/tasks on the same hardware at (apparently) the same time.
* **Inter-Process Communication** (IPC): the ability for two different programs to communicate with each other.
* **Address space management**: manages how the available (RAM) memory is divided between programs.

These three mechanisms form the core of an OS and will be elaborated on in the remainder of this course.

### System calls

The area marked in <span style="background-color: yellow">&nbsp;yellow&nbsp;</span> in the figure above is called the **user mode**. The area marked in <span style="background-color: red; color: white">&nbsp; red &nbsp;</span> in the figure above is called the **kernel mode** or the **privileged mode**. A program in user mode has no direct access to the hardware or to the entire memory space: it has to go through the kernel first. 

When the user, or the software on the user's behalf, needs something from the more privileged world, the border between the user mode and kernel mode needs to be crossed. This is done using special functions that facilitate this, called **System Calls**. A list of all the system calls in a Linux operating system can be found [here](http://asm.sourceforge.net/syscall.html#p31). These include methods to start a new program, send a message to a different program, read from a file, allocate memory, send a message over the network, etc.

These System Calls form the **API** (Application Programming Interface) between the higher-level software/applications in user mode (what you will typically write) and the lower-level features and hardware in kernel mode.

## Linux

Since there are many OSes, we can of course not discuss them all. Most are however very similar in concept and in the basic systems they provide. As such, we will mainly focus on explaining these basic mechanisms in this course (see above).  

Still, to be able to get some hands-on experience with these systems, we need to choose one OS: the **Linux OS**. We do this because it is a very advanced and stable OS that is used extensively worldwide, and because it is open source (meaning that, unlike Windows and MacOS, we can view all the code in the kernel and even change it). 

The Linux kernel almost never comes on its own but is packaged in a distribution (a.k.a. a "distro"). Such a distro is the combination of various pieces of software and the linux kernel. A distro can for example include a Graphical User Interface (GUI) layer, Web browsers, file management programs etc. As such, there is a large number of Linux distributions available, which mainly differ in the additional software they provide on top of the Linux kernel (which is pretty much the same across distros). Which one to pick was (and probably is) the start of multiple programmer wars, as everyone has their own preference. Our recommendation is to take into consideration what you want to use it for. For example when using Linux on a Web server, you probably don't need a full GUI or a Web browser, which is different from when you want to use it as your main OS on your laptop. 

{{< figure src="https://upload.wikimedia.org/wikipedia/commons/1/1b/Linux_Distribution_Timeline.svg" title="source: Wikimedia" >}}


If the figure above doesn't contain a distribution to your liking you can always Do It Yourself: [Linux from scratch](http://www.linuxfromscratch.org/). Happy compiling !!


One of the main aspects in which these distro's differ is the packaging system with which it's distributed. These packaging systems allow you to install/uninstall/... your software (a bit like the Windows Store or the mobile App Stores, but with more control over individual software libraries). The people that are making distro's take source code from main software packets and compile them using the distro's dependencies. This is then packaged and made available for package managers to install from. Typical examples of package mangers are:

| Name | Extension | Typical distro's |
|---|---|---|
| dpkg | .deb | Debian and Ubuntu a.o.|
| RPM | .rpm | Red Hat, Fedora, and CentOS a.o. |
| packman | .pkg.tar.xz | Arch Linux, FeLi Linux a.o. |

{{% notice note %}}
If you search for Bodhi in the image above, you'll learn that Bodhi is based on Ubuntu, which is based on Debian. Therefore APT (Advanced Package Tool) is used. This is why we used `apt install SOFTWARE_NAME` when setting up our Virtual Machine.
{{% /notice %}}

{{% task %}}
1. Use apt to see a list of the installed packages in the VM
2. Update the list of packages in the VM
3. Upgrade all packages to the most recently available version
4. Install **frozen-bubble** in your VM

(tip: adding -h or --help to a Linux command typically shows you the main options. Try `apt -h`.)
{{% /task %}}


## Got Root ?
Most operating systems allow for multiple users to share one system and provide ways to clearly separate those users (and what they can access) from each other. Like in most OSes, Linux also has an **administrative** user, or super-user: the **root** user, who can access -everything- on the system. This highly privileged user is typically not used when doing day-to-day work, as it can be dangerous (for example, the root user can remove all files on the hard drive with a single command).

A better way of approaching your day-to-day work on a Linux system is to use a standard user. Whenever you need a higher privilege-level, you can use **sudo** (Super User DO). This is a simple tool that allows a regular user to execute only certain commands as the root-user (only when needed). In your VM, your main user that you use to login with is normally also the root user, but you still need to use "sudo" to execute sensitive commands. 

{{% figure src="https://imgs.xkcd.com/comics/sandwich.png" title="source: xkcd.com"%}}

Every user that has a login on a Linux system also automatically belongs to a **group**. Depending on the distribution, this group can have multiple names. On **Bodhi** for example, a new group is created for every user that bares the same name. Linux allows you to assign certain privileges and access rights to entire groups at a time, instead of only to individual users. 

{{% task %}}
Find the single command that can remove all files on the hard drive online (but please don't try it!)
{{% /task %}}

## On files and such

On Linux, almost everything is a file. A file is a file. A directory is a file. An entire harddrive is a file. A UART port is a file. Even a network connection is a file! Every file is owned by one user. All other users' privileges for that file (read, write, execute) are based on the **access permissions**.

{{% figure src="/img/os/accesspermissions.png" title="Access permissions in an example folder"%}}

The image above shows the content of a folder **example** this folder contains: 2 files, 2 directories, a *hidden* directory (.secretfolder), and a *hidden* file (.ssshhhtt.txt). With *hidden* is meant that these files are not seen with a normal *ls*. To see these files the **-a** options has to be present. In Linux, all files starting with a "dot" character (.) are hidden and are often called "dotfiles". They are often used to store configuration metadata; for example, git repositories have a .gitignore file with a list of files/directories that should not be included in the version control system.

You will also notice two special/strange entries at the top of the `ls -al` output, named "." and "..". These are not real files on the disk, but rather virtual files that help navigation in the filesystem and the execution of commands. Firstly, the ".." always means "the parent of this directory". So if you are at the path "/home/user/test" and you do `cd ..`, you will automatically go to "/home/user". Doing `cd ../..` will go to "/home". Secondly, the single dot "." means "the current directory". This comes in handy if you want to search for something in files in the current directory or copy something to where you are at that moment without having to type the entire path. 

With the **-l** parameter for `ls` the *long listing* format is shown (as is seen in the image above). With this, the access permissions are shown in the first 10 characters of each line:

{{% figure src="https://1.bp.blogspot.com/-4YYentw6dEM/W2WjhM1l1DI/AAAAAAAAL6M/2pJn_KbDXmUPEImvikiCFcnWJ0pLvzVVACLcBGAs/s640/UNIX%2Bfile%2Bpermissions%2Bby%2BJulia%2BEvans.jpg" title="source: drawings.jvns.ca"%}}

The first character indicates whether the entry is a directory (d) or a file (-). 


## Out of fuel ? Take a Shell

When a user logs in on a Linux computer, typically one of the following approaches is used:

* a login through a Graphical User Interface (GUI)
* a login through a Command Line Interface (CLI)

For a desktop/laptop that is running Linux, the GUI approach is typically used. An example is the Ubuntu/Bodhi Virtual Machine you use for the labs. On those systems there are **terminal emulators** which emulate the CLI. Many flavours of these terminals are available: gnome-terminal, xterm, konsole, ...

{{<figure src="http://linuxcommand.org/images/adventure_powerterm_gnome_terminal_with_tabs.png" title="Example of a Terminal emulator. Source: linuxcommand.org">}}

For embedded systems or Linux running on servers, the CLI is more appropriate. Running the Graphical User Interface requires CPU time and storage. Both are scarce on an embedded system. Since everything can be done through the command line, removing the GUI is a win-win. Additionally, it is useful to learn the CLI commands even if you normally use the GUI, because they play a large part in writing automation scripts for the OS: automation scripts typically do not indicate commands like "click button at location x,y" but rather execute the necessary CLI commands directly.

When a CLI is used in Linux (or an emulator), a **shell** is started. The shell is a small program that translates commands, given by the user, and gives these translations to the OS. As with anything, there are many flavours of shells: sh, bash, ksh, zsh, ... Most shells provide the same basic commands, but others allow additional functionality and even full programming environments. You can write so-called "shell scripts" (typically have the file extension ".sh"), which are mostly lists of CLI commands, that are used extensively to automate operations on Linux systems.

Once the shell is running and the user asks to create new processes, all of these newly create processes will have the shell as a parent process (this will become important later on).

{{% notice note %}}
As a side note: Linux is not the only OS that uses a CLI. Windows for example has multiple, including the older "Command Prompt" and the more recent "Powershell". 
{{% /notice %}}