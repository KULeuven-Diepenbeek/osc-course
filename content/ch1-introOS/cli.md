---
title: '1.3: Getting your CLI-feet wet'
pre: "<i class='fas fa-vial'></i> "
weight: 3
---

<center><video src="/img/os/b.mp4" autoplay loop style="width: 60%"></video>
<br/>Source: Neo</center>

## Getting your feet wet

This 'lab' consists of a list of small tasks that introduce you to the command-line interface. None of these tasks should require exhaustive manual labour. Most can be accomplished by using the commands you already know (and that are listed at the [cheat sheet](/appendix/cheat_sheet)), and for others a short Google session should give you the answer.

### Navigation
1. figure out in which folder you are at the moment
2. navigate to the *root* folder of the OS
3. navigate to your home folder (/home/username), without actually typing that path
4. make an **alias** (`man alias`) that navigates to your home folder from everywhere within the system

### File manipulation
1. make a folder "myVeryOwnFolder"
2. navigate into that folder
3. create a file: **hello.txt** that contains the text **hello world**. Do this in a single step (hint: you can "pipe" commands together)
4. move up on folder and remove the entire directory myVeryOwnFolder, including the .txt file

### Access permissions
1. create a new file with any content
2. make this file read-only for everyone
3. remove the file
4. make a folder **ToBeDeleted**
5. remove the *execute* rights from this folder for ALL users
6. remove this folder

### Various
1. navigate to osc-exercises/ch5_os (from your cloned git repository)
  * all these files contain random text
  * one file contains the word "bamboozle"
  * find out which file contains this word
  * find out the line number on which the word occurs
2. **search** the man page for the meaning of "-x" in the command *ls*
3. display the current date and time (is this correct? Why wouldn't it be?)
4. execute three commands, using the **enter** key only once
  1. display the current date and time
  2. sleep for 10 seconds
  3. display the current date and time