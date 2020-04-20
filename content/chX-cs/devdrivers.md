---
title: 'X.3: Device Drivers'
pre: "<i class='fab fa-linux'></i> "
weight: 3
draft: true
---

## General
The kernel of an operating system has a lot of different tasks. Some of them we visited in earlier chapters. One task of the OS is the management of the different hardware **devices** that are typically connected to a processor in a laptop, desktop, or server. The OS has to know **how** to talk to a certain device. Typically an Application Programming Interface (an **API**) is provided to the user space, so users can interact with the hardware.

Let's take the timer from [chapter 2](../../ch2-interrupts/theory2_timer/) as an example. Enabling the interrupt for when Timer1 overflows was done by writing a '1' to the LSB of address 0x6F. Although this is no rocket science, it is not realistic to assume that the user *simply knows this*. The manufacturer of the hardware, the timer in this example, is the one that knows and should make this knowledge available to the user. This is typically done through documentation, or through a driver.

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

The argument of needing additional software, e.g. the driver, is no longer a concern. The additional kilobyte of "firmware" can easily be stored. An additional benefit from using a driver is that it provides a more flexible solution. For example, version 2.0 from our timer has this bit moved to another position in the register. The "skilled" user that uses the timer, has to update his/her source code. With the solution of a driver, the vendor simply ships an updated driver with the hardware and no modifications needs to be made by the user.


## Character device drivers

## Block device drivers
