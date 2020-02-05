---
title: 'Engineering notes'
draft: true
---

# Wouter

* &nbsp;

# Jo

## Varia
* Installing kernel sources:
  * sudo apt-get update
  * sudo apt-get upgrade
  * uname -r          gets release 
  * uname -v          gets version
  * lsb_release -c    get codename of debian release
  * sudo apt-get source linux-source

## Linux device driver

info: 
* Free Electrons

### Virtual memory mgmt

MMU: virtual -> physical
1. kernel space: kernel & device drivers
top 1GB: 0xC0000000 - 0xFFFFFFFF

2. user space: user application software
bottom 3GB: 0 - 0xBFFFFFFF

(this 3/4 - 1/4 are configurable in the kernel)
(kernel space virtual addres 0xc0000000 maps to phiscal address zero - might be kernel version dependent)

Linux uses processor modes to create privilge levels

Library functions run in user apce

system calls:
* in kernel mode on the user's behalf
* in supervisor mode if trigger by library function
* after execution back to user mode
* user space application is typically blocked until library function and systelm call return

### Linux device model
* Linux Device model is built around the concept of busses, devices and drivrs.
* All devices are connect to a bus (of some kind)
* a bus might be a softwar abstraction of a real us
* when a device si found to match a driver ==> boudning

Device types:
network devices (use ifconfig to see them)
block devcies: to raw storage (HD, USB key, ...) (vis as /dev)
character devices (to all other types)(vis as /dev)
mtd devices: flashmemory

### Virtual File system
* system and kernel info in the VFS
* 2 virutal fs's are knwo
  * proc /proc (older mechanism and a bit chaotic)
  * sysfs /sys info of the system as a set of decies buses, ...

Sysfs: kernel exports operating details to user space
  * /sys/bus list of buses
  * /sys/devcies contains the lit of devices
  * /sys/class enumberate devices by class unregarding the bus they are connected to

### kernel modules
* linux kernel: modular monolithic kernel
* moduels are usefull to recude boot time, reduce kernel size
* once loaded, modulers have full control and privlieegdes on the system
* naming conventions: <fname>.ko
* location: lib/modules/<kernel_version>
* are not device drivers by definitons

hello world for kernel modules
```C
#include <linux/init.h>
#include <linux/module.h>

static int __init simple_init(void) {
  printk(KERN_ALERT "Hello World\n");
  return 0;
}

static void __exit simple_exit(void) {
  printk(KERN_ALERT "Goodbye\n");
}

module_init(simple_init);
module_exit(simple_exit);
```