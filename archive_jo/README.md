 
# Captain's log
'k Heb een install gedaan op een virtual machine om het een en ander uit te proberen. Na de gewoonlijke installatie van een OS ([Bodhi Linux](http://www.bodhilinux.com/)) in een virtual box (met extra harde schijf), is dit het stappenplan:

Local folder
```
cd ~
mkdir mbed
cd mbed
```

Supporting i386 architecture
```
sudo dpkg --add-architecture i386
sudo apt-get update
sudo apt-get install libc6:i386 libncurses5:i386 libstdc++6:i386
```

Install git
```
sudo apt-get install git
```

Updating python/pip
```
sudo apt-get install python-pip
sudo pip install --upgrade pip
```

Installing mbed-cli
```
sudo pip install mbed-cli
```

Installing GNU Arm Embedded toolchain
```
bunzip2 ~/Downloads/gcc-arm-none-eabi-6-2017-q2-update-linux.tar.bz2
cd /opt
sudo tar -xf gcc-arm-none-eabi-6-2017-q2-update-linux.tar
```

Running blinky
```
cd ~
cd mbed
mkdir blinky
cd blinky
mbed import mbed-os-example-blinky
cd mbed-os-example-blnky/mbed-os
sudo pip install -r requirementx.txt
```

Compiling
```
cd ~/mbed/blinky/mbed-os-example-blinky
mbed toolchain GCC_ARM
mbed target nuleo_l073rz
mbed compile
```
