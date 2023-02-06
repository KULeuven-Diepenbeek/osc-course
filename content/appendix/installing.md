---
title: '2. Linux Installation Instructions'
---

The exercises for this course are to be done on the **Linux** Operating System (OS). For those unfamiliar, Linux is an open source OS that comes in many different forms called distributions. Linux is used extensively worldwide and you will need to use it many times in your future career.

We would of course not ask you to remove Windows to install Linux on your personal machine. Installing both OSes side-by-side (called a _"dual boot"_) is also a very valid option. Please see the [Ubuntu Install Guide](https://ubuntu.com/tutorials/install-ubuntu-desktop#1-overview) if you'd like to install Linux permanently. Make sure not to erase your existing Windows partition! We are _not_ responsible and will _not_ be able to help if something went wrong.  

For this course, we provide a third option, called a _"virtual machine"_. We will install Linux inside of your Windows OS through an additional program called VirtualBox, which will make Linux think it's running on normal hardware.

Notes:

* If you are already using Linux on your laptop, you can skip steps 1-4 below, but make sure you do steps 5-6!
* If you are using MacOS, you should still install a Linux flavor. Even though MacOS also runs on a flavor of UNIX, they are not fully compatible. For instance, you will not be able to compile and run the device driver exercises.
    - If you are using a 2020+ M1 Apple Mac architecture (ARM64 - click on "apple" - "about": does "Chip" say "Apple M1"?), then you should try out the QEMU-based Mac-specific virtualization alternative called [UTM](https://mac.getutm.app/). Follow [the UTM docs](https://docs.getutm.app/guides/ubuntu/) on how to install Ubuntu. Don't forget to choose "virtualize" and mount [the ARM64 `.iso`](https://ubuntu.com/download/server/arm)---not the AMD one. Bodhi Linux only works in "emulate" mode and is _very_ slow.
    - If that still doesn't work, try [VMWare Fusion](https://www.vmware.com/products/fusion.html), a personal edition is free.


## OSC VirtualBox Install Guide

1. Download and install [VirtualBox](https://www.virtualbox.org/)
2. Download Linux
    * There are many types of Linux available. We will use either Ubuntu or Bodhi (which is a more lightweight, smaller version of Ubuntu)
        * download [Ubuntu](https://ubuntu.com/download/desktop) (choose the Ubuntu 22.04.1 LTS, filename ubuntu-22.04.1-desktop-amd64.iso) (3.6 GB image, will require 10GB+ disk space)
        * OR download [Bodhi](https://www.bodhilinux.com/download) (choose the Standard release, filename bodhi-6.0.0-64.iso) (800MB image, will require 6GB disk space)
    * We strongly recommend you use Ubuntu if possible

3. Prepare VirtualBox
    * For this first part, we will follow [an existing guide](https://brb.nci.nih.gov/seqtools/installUbuntu.html). You can also simply read along the official [Ubuntu VirtualBox install guide](https://ubuntu.com/tutorials/how-to-run-ubuntu-desktop-on-a-virtual-machine-using-virtualbox#1-overview).
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
    * We will do this from the "terminal" or "command line", a textual interface. This comes pre-installed in Linux. Look for an [icon like this one](https://upload.wikimedia.org/wikipedia/commons/thumb/d/da/GNOME_Terminal_icon_2019.svg/1200px-GNOME_Terminal_icon_2019.svg.png), which should open a screen that looks a bit like [this one](https://ubuntucommunity.s3.dualstack.us-east-2.amazonaws.com/optimized/2X/b/ba76cbf3dc8dc2cc94d26dd61c7aad3cedcd5102_2_690x300.png).
    * To check if GCC is installed (it should be), type the following command in the terminal and hit enter: `gcc -v`
        * the output should be a list of details of the GCC program, and should end with a line starting with "gcc version"
        * if this is not the case and you get an error message saying GCC is not installed, please execute the following command `sudo apt update && sudo apt install -y gcc` (it will ask you for your password) and try again

6. Get the course files
    * For some exercises, we provide some basic code to help you get started
    * This code is hosted in a [GitHub repository](https://github.com/KULeuven-Diepenbeek/osc-exercises). If that sounds like Gobbledygook to you, no worries: the Software Engineering course will explain all about Git and version control soon
    * For now, you just need to execute following commands in the terminal:
        * Install git: `sudo apt update && sudo apt install -y git`
        * Go to your home directory: `cd ~/`
        * Download the course files: `git clone https://github.com/KULeuven-Diepenbeek/osc-exercises.git course-files`
            * This will create a new directory named "course-files" containing the necessary items. You can verify this by typing `ls -la`


You should now be ready to follow along with the classes! 

## FAQ

- [WINDOWS] The screen looks very interlaced
    - Settings > Display
    - Graphics Controller VBoxVGA -> VMSVGA
- I want to change the keyboard layout!
    - See https://www.bodhilinux.com/w/configuring-your-new-bodhi-system/: Go to Menu > Applications > System Tools > System Settings > Keyboard Layout to open the Keyboard Layout dialog box.  Click your language from the list and hit Apply Selected.
- I want to be able to copy-and-paste text between my Host (my own computer) and the Guest (Linux ISO)!
    - This is not possible without the installation of an additional package: https://askubuntu.com/questions/22743/how-do-i-install-guest-additions-in-a-virtualbox-vm/22745#22745
- I want to install something else such as my own favorite editor!
    - `sudo apt install [package]`. Read It's FOSS's [Ubuntu Getting Started Guide](https://itsfoss.com/getting-started-with-ubuntu/).
- I want to change the resolution of the VirtualBox display
    - This is sadly non-trivial with VirtualBox, where by default you can either choose the small/windowed view (default), or a fullscreen view from the menu.
    - To choose a dynamic resolution, you need to install the "VirtualBox Guest Additions"
        - Boot the Virtual Machine and login
        - In the VirtualBox menu on top, choose "Mount Guest Additions CD Image" (bottom option)
    - This should allow you to auto-install the necessary software. After this, reboot the VM and you should be able to choose new screen sizing options in the VirtualBox View menu
        - Sometimes this step requires additional software to be installed first. This typically does the trick: `sudo apt install -y make perl`. After this, reboot the VM and re-Mount the CD image. 

If you encounter any other issues, Google is your friend. There's a high chance others have encountered the same problem as you have, and have posted a solution.
