---
title: '2. Linux Installation Instructions'
---

The exercises for this course are to be done on the **Linux** Operating System (OS). For those unfamiliar, Linux is an open source OS that comes in many different forms called distributions. Linux is used extensively worldwide and you will need to use it many times in your future career.

We would of course not ask you to remove Windows to install Linux on your personal machine and installing them side-by-side (called dual boot) is also a hassle. So for this course we use a third option, called a "virtual machine". We will install Linux inside of your Windows OS through an additional program called VirtualBox, which will make Linux think it's running on normal hardware.

Notes:
* if you are already using Linux on your laptop, you can skip steps 1-4 below, but make sure you do steps 5-6!
* if you are using MacOS, you should still install VirtualBox. Even though MacOS also runs on a flavor of UNIX, they are not fully compatible. 

## Recipe for installing the OSC virtual machine

1. Download and install [VirtualBox](https://www.virtualbox.org/)

2. Download Linux
    * There are many types of Linux available. We will use either Ubuntu or Bodhi (which is a more lightweight, smaller version of Ubuntu)
        * download [Ubuntu](https://ubuntu.com/download/desktop) (choose the Ubuntu 20.04.2 LTS, filename ubuntu-20.04.2-desktop-amd64.iso) (2.7GB image, will require 10GB disk space)
        * OR download [Bodhi](https://www.bodhilinux.com/download) (choose the Standard release, filename bodhi-5.1.0-64.iso) (800MB image, will require 6GB disk space)

3. Prepare VirtualBox
    * For this first part, we will follow [an existing guide](https://brb.nci.nih.gov/seqtools/installUbuntu.html)
        * Note that this is for an older version of Ubuntu, but everything is the same up until where you need to actually install Linux (the "Install Ubuntu" heading), which is where you go to step 4 below
    * Follow the guide until the "Install Ubuntu" Heading, taking into account these changes/options:
        * Memory size:
            * Best to choose at least 2048MB of RAM for the Virtual machine
        * Disk size:
            * For Ubuntu: choose a disk size of at least 10GB
            * For Bodhi: choose a disk size of at least 6GB
            * For both: you may choose the "Dynamically allocated" disk for this course if you don't have much disk space on your machine

4. Install Linux
    * In theory, you can run Linux without installing it (the "Try Ubuntu" option or the default state that Bodhi starts in). However, you would loose all files every time you shutdown the Virtual machine, so we recommend installing it proper for the duration of this course
    * For Ubuntu:
        * Ubuntu starts into a selection screen where you can choose to either Try Ubuntu or install it. Choose install.
        * Follow the default installation instructions in the wizard (similar to [the guide we've been following](https://brb.nci.nih.gov/seqtools/installUbuntu.html))
        * You can safely erase the disk: this only erases the virtual disk, not your real hard drive
        * You do NOT need to choose additional encryption
    * For Bodhi:
        * Bodhi starts into a selection screen with several options. You need to be fast, because after a while it auto-selects the first option (= try without installing). Instead, use the arrow keys to choose "Install Bodhi"
        * Follow the default install wizard, choosing the default options
        * You do NOT need to choose additional encryption
    * After installation, reboot and login with your created account

5. Prepare GCC
    * For many exercises in this course, we will use the "GNU Compiler Collection" (GCC) to run our C program code. 
    * We will do this from the "terminal" or "command line", a textual interface. This comes pre-installed in Linux. Look for an [icon like this one](https://kuleuven-diepenbeek.github.io/), which should open a screen that looks a bit like [this one](https://ubuntucommunity.s3.dualstack.us-east-2.amazonaws.com/optimized/2X/b/ba76cbf3dc8dc2cc94d26dd61c7aad3cedcd5102_2_690x300.png).
    * To check if GCC is installed (it should be), type the following command in the terminal and hit enter: `gcc -v`
        * the output should be a list of details of the GCC program, and should end with a line starting with "gcc version"
        * if this is not the case and you get an error message saying GCC is not installed, please execute the following command `sudo apt update && sudo apt install -y gcc` (it will ask you for your password) and try again

6. Get the course files
    * For some exercises, we provide some basic code to help you get started
    * This code is hosted in a [GitHub repository](https://github.com/KULeuven-Diepenbeek/osc-course). If that sounds like Chinese to you, no worries: the Software Engineering course will explain all about Git and version control soon
    * For now, you just need to execute following commands in the terminal:
        * Install git: `sudo apt update && sudo apt install -y git`
        * Download the course files: `git clone https://github.com/KULeuven-Diepenbeek/osc-course.git course-files`
            * This will create a new directory named "course-files" containing the necessary items


You should now be ready to follow along with the classes! 

## FAQ

1. [WINDOWS] The screen looks very interlaced
  * Settings > Display
    * Graphics Controller VBoxVGA -> VMSVGA
2. I want to change the keyboard layout!
  * (https://www.bodhilinux.com/w/configuring-your-new-bodhi-system/ Go to Menu > Applications > System Tools > System Settings > Keyboard Layout to open the Keyboard Layout dialog box.  Click your language from the list and hit Apply Selected.)
3. I want to be able to copy-and-paste text between my Host (my own computer) and the Guest (Linux ISO)!
  * This is not possible without the installation of an additional package: https://askubuntu.com/questions/22743/how-do-i-install-guest-additions-in-a-virtualbox-vm/22745#22745
4. I want to install something else such as my own favorite editor!
  * `sudo apt install [package]`
5. I want to change the resolution of the VirtualBox display
  * View -> fit to screen, or View -> change resolution to -> pick one.

<!-- 6. I get the following error **can't open device "/dev/ttyACM0": No such file or directory**. This means that the Arduino is not present in the Virtual Machine. Make sure you've added the device in the **OSC - Settings** !! 
{{% figure src="/img/installVM/arduino_01.png" %}}
  * This can be verified with the command **lsusb**. If the Arduino is not found, it should not be present in the result of this command:
{{% figure src="/img/installVM/arduino_02.png" %}}
  * In the bottom right of your VirtualBox machine, you can give permission to your Arduino on the VM:
{{% figure src="/img/installVM/arduino_03.png" %}}
  * The VM should now be able to see the Arduino. Again ... verify with **lsusb**
{{% figure src="/img/installVM/arduino_04.png" %}} -->

