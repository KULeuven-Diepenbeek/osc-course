---
title: '2. Installation Instructions'
---

The exercises for this course are to be done on a **Linux** machine. Because it is not expected that you reinstall your machines (or prepare them for dual boot) there is a virtual machine prepared for you :smiley:. This virtual machine runs [Bodhi](https://www.bodhilinux.
com/) which is a lightweight linux distribution that is based on Ubuntu 18.04 LTS.

## System Requirements

The most crucial resource is disk space. The virtual machine image is **2.4 GB** and will be **5.2 GB when extracted**. The downloaded image can be removed after installation.


## Recipe for installing the OSC virtual machine

1. download and install [VirtualBox](https://www.virtualbox.org/)
2. download *OSC.ova* image: [OSC.ova](http://eaict.technologiecampusdiepenbeek.be/~jvliegen/OSC.ova)
3. start VirtualBox
  * Under File > Import Appliance ...
  * choose *OSC.ova*
{{% figure src="/img/installVM/04_import.png" %}}
    * reinitialise MAC addresses of all Network cards
    * click Import
  * wait and have a &nbsp; <i class="fas fa-mug-hot"></i>
4. Select the **OSC** image and go to *Settings*
{{% figure src="/img/installVM/01_settings.png" %}}
  * Plug in your Arduino
  * Goto USB
{{% figure src="/img/installVM/02_usb.png" %}}
  * With USB 1.1 selected, add a USB device (the Arduino)
{{% figure src="/img/installVM/03_usb.png" %}}
5. launch the Virtual Machine ... Welcome to Bodhi !!
{{% figure src="/img/installVM/05_bodhi.png" %}}

## FAQ

1. [WINDOWS] The screen looks very interlaced ()
  * Settings > Display
    * Graphics Controller VBoxVGA-> VMSVGA


