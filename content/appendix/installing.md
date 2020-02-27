---
title: '2. Installation Instructions'
---

The exercises for this course are to be done on a **Linux** machine. Because it is not expected that you reinstall your machines (or prepare them for dual boot), there is a virtual machine prepared for you :smiley:. This virtual machine runs [Bodhi](https://www.bodhilinux.
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

1. [WINDOWS] The screen looks very interlaced
  * Settings > Display
    * Graphics Controller VBoxVGA -> VMSVGA
2. I want to change the keyboard layout!
  * (https://www.bodhilinux.com/w/configuring-your-new-bodhi-system/ Go to Menu > Applications > System Tools > System Settings > Keyboard Layout to open the Keyboard Layout dialog box.  Click your language from the list and hit Apply Selected.)
3. I want to be able to copy-and-paste text between my Host (my own computer) and the Guest (Bohdi Linux ISO)!
  * This is not possible without the installation of an additional package: https://askubuntu.com/questions/22743/how-do-i-install-guest-additions-in-a-virtualbox-vm/22745#22745
4. I want to install something else such as my own favorite editor!
  * `sudo apt-get install [package]` (root password is XXXXXX)
5. I want to change the resolution of the VirtualBox display
  * View -> fit to screen, or View -> change resolution to -> pick one. 
6. I get the following error **can't open device "/dev/ttyACM0": No such file or directory**. This means that the Arduino is not present in the Virtual Machine. Make sure you've added the device in the **OSC - Settings** !! 
{{% figure src="/img/installVM/arduino_01.png" %}}
  * This can be verified with the command **lsusb**. If the Arduino is not found, it should not be present in the result of this command:
{{% figure src="/img/installVM/arduino_02.png" %}}
  * In the bottom right of your VirtualBox machine, you can give permission to your Arduino on the VM:
{{% figure src="/img/installVM/arduino_03.png" %}}
  * The VM should now be able to see the Arduino. Again ... verify with **lsusb**
{{% figure src="/img/installVM/arduino_04.png" %}}

