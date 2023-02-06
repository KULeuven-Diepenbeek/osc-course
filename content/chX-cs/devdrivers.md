---
title: 'X.3: Device Drivers'
pre: "<i class='fab fa-linux'></i> "
weight: 3
---

## General
The kernel of an operating system has a lot of different tasks. Some of them we visited in earlier chapters. One task of the OS is the management of the different hardware **devices** that are typically connected to a processor in a laptop, desktop, or server. The OS has to know **how** to talk to a certain device. Typically an Application Programming Interface (an **API**) is provided to the user space, so users can interact with the hardware.

Let's take the timer from [chapter 3](/ch3-interrupts/theory2_timer/) as an example. Enabling the interrupt for when Timer1 overflows was done by writing a '1' to the LSB of address 0x6F. Although this is no rocket science, it is not realistic to assume that the user *simply knows this*. The manufacturer of the hardware, the timer in this example, is the one that knows and should make this knowledge available to the user. This is typically done through documentation, or through a driver.

<div class="multicolumn">
  <div class="column">
    {{% highlight c %}}
      ...
      #define TIMSK1 _SFR_MEM8(0x6F)
      ...
      TIMSK1 |= 0x1;
      ...
    {{% /highlight %}}
    <p>The user could find out what is to be done to enable the interrupt from the documentation. When that is figured out, the user has to program/use the functionality correctly.</p>
    <ul> 
      <li><i class="fas fa-plus-circle"></i> This needs no additional software</li>
      <li><i class="fas fa-minus-circle"></i> This requires a "skilled" user</li>
    </ul>
  </div>
  <div class="column">
    {{% highlight c %}}
      ...
      #include "timer.h"
      ...
      enable_interrupt_timer1_overflow();
      ...
    {{% /highlight %}}
    <p>The user could find out what is to be done and execute the dedicated function.</p>
    <ul> 
      <li><i class="fas fa-plus-circle"></i> This requires a "normal" user</li>
      <li><i class="fas fa-minus-circle"></i> This needs additional software</li>
    </ul>
  </div>
</div>

The argument of needing additional software, e.g. the driver, is no longer a concern. The additional kilobyte of "firmware" can easily be stored. An **additional** benefit from using a driver is that it provides a more flexible solution. For example, version 2.0 from our timer has this bit moved to another position in the register. The "skilled" user that uses the timer, has to update his/her source code. With the solution of a driver, the vendor simply ships an updated driver with the hardware and no modifications needs to be made by the user. **Scalability** is improved!

### Where do they live ?
The driver is a piece of software that allows an operating system to interact with a certain hardware component. In the first lecture on OSes, we talked about the user-space and kernel-space. So, where do device drivers live ? Take a guess ... I'm sure you'll be correct.

The correct answer is: both :smile: The driver can live in user-space and in kernel-space. Depending on the space, there is a benefit and drawback. Drivers in user-space will not crash the entire system is an error occurs in the driver itself. This provides improved **stability**. Drivers in kernel-space will run with much higher priority than user-space processes ever can. This provides improved **performance**. 


## Character device drivers
Character devices are the simplest types of devices to communicate with, on a Linux systems. The textbook example for this is a **serial port**. The serial port is the predecessor of the Universal Serial Bus (USB). Students might have been in contact with the serial port when using the RS232 protocol. This is how the UART communicates. Today, it is hard to find the original connector on a modern laptop/desktop, as they are all replaced with a USB-alternative.

<div class="multicolumn">
  <div class="column">
    {{% figure src="/img/nullmodem.jpg" width="55%" title="The original serial port cable" %}}
  </div>
  <div class="column">
    {{% figure src="/img/usbconnectors.jpg" title="Different types of USB connectors" %}}
  </div>
</div>

As was stated before in the course, **everything** is a file on a Linux operating system. The serial port, which is driven by a **character device driver**, is represented by a file in */dev*

{{% figure src="/img/chx/ttyusb0.png" title="The representation of a serial port on Linux system" %}}

The first character of *permission modes* is a **c**. We have seen that a **d** represents a directory. The **c** here shows that the device is a character device. A **character device** is a device that works with **one character** as a basic unit. The user can read one character at a time, or write one character at a time. As state above, the serial port is an excellent example for this.


## Block device drivers

Devices that support **filesystems** are referred to as block devices. The drivers, not surprisingly: block device drivers. The typical examples for these are hard drives, solid-state drives, and USB flash memories.

Similar to the letter **c** with the character devices in the permissions, the block devices show the letter **b**.

{{% figure src="/img/chx/block_device.png" title="The representation of a solid-state drive on Linux system" %}}


## Writing your own

When you develop new hardware, or got in a situation where no drivers are around for existing hardware, you might decide it is time to write your own device driver.

This type of programming is very different from general application programming as you know it. If you make mistakes with general programming, you get a fault and that's that. Maybe you need to reset the terminal, but that's (roughly speaking) the worst that can happen.

When you write bugs in your device drivers, it is a different story. Memory leaks in the kernel might crash your system periodically. Incorrectly handled exceptions lead to system failures and maybe even hardware failures.

### Kernel modules
Earlier we have seen that the kernel is not one impenetrable binary (monolithic). The kernel can be expanded with **kernel modules**. This is a *small* piece of code that can be added to the kernel, while the kernel is running. A number of kernel modules are present in the Virtual Machine image. You can **list** the kernel **modules** with the command: lsmod.

{{% figure src="/img/chx/lsmod.png" title="Result of lsmod in the Virtual Machine" %}}

Modules can be loaded and unloaded with **insmod** and **rmmod**, respectively.

### Driver
While developing your custom driver, it is recommended you start of with a kernel module. After compiling, the kernel module can be inserted into the kernel (and hopefully, don't crash it).

Because the driver is a **kernel module** it also has no **main()** function. "It's just" a collection of functions that are attached to **hooks** of the kernel.

```C
    int register_blkdev(unsigned int major, const char *name);
```

For example: the *hook* above is a standard function that kernel provides to allow a driver for a block device to register itself with the kernel.

Displaying messages on the **standard output device** is also not possible. Beginning kernel hackers use the printk function:

```C
    printk(KERN_DEBUG "Debug message shown!\n");
```

These printed message do not end up on the device's monitor, but in the kernel ring buffer. A **ring buffer** is a buffer with a fixed amount of size. When overflowing, the oldest messages get deleted.

The ring buffer can be consulted using the **dmesg** command. This prints the current content of the ring buffer to the screen.

<div class="multicolumn">
  <div class="column">
    {{% figure src="/img/chx/dmesg_1.png" title="Example of dmesg output" %}}
  </div>
  <div class="column">
    {{% figure src="/img/chx/dmesg_2.png" title="Example of dmesg, after inserting a USB drive" %}}
  </div>
</div>


{{% notice note %}}
This is also a good place to visit when you are trying to solve system problems !!!!

{{% /notice %}}