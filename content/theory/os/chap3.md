---
title: 'Chapter 3: Task management'
---
<!--
&laquo;&nbsp;[Back to Table of Contents](/)<br/>

<hr/>
< !--
&raquo;&nbsp;[Naar de labo opgave](#oef)
-->

# 3.1 Task management
One of the three core tasks of an OS is the management of tasks. These different tasks are all running on the same processor. To make this magic happen some form of management is required.


## 3.1.1 Got task ?
<div style="background-color: #F00; color: yellow; font-weight: bold; text-align: center">TODO: Uniformly style definitions ?</div>
By definition, a process is an instance of a program. As was dicussed in the "C-portion" of this course a basic program can be divided in multiple segments:

* **text/code**: is the machine code in assembly. This section is compiled for one (type of) processor(s).
* **data**: is the segment that contains initialised variables. These variables could be global, static, or external. A further distinction can be made between normal initialised variables and constants. This distinction is often referred to with read-only (ro-data) and read-write (rw-data), with the former the part where the constants reside and the latter that of the normal variables.
* **bss**: this segment contains the global and static variables that are not initialised.

When source code is compiled into a binary, these segments are *fixed*. 

Let's put these definitions to the test. A very simple program could be written as follows:
```C
#include <stdio.h>

int main(void) {

  printf("hello world !\n");

  return 0;
}
```

This program can be compiled with the command below:

```bash
jvliegen@localhost:~/$ gcc -o eg3_1 eg3_1.c

jvliegen@localhost:~/$ 
```

On the command line there is a command **size** that can be used to examine these segments. The arguments that are available on Linux commands can typically be explored with **command --help** or **man command** (offcourse, command needs to be replaced with the actual command-name).

```bash
jvliegen@localhost:~/$ size -B eg3_1
   text    data     bss     dec     hex filename
   1516     600       8    2124     84c eg3_1

jvliegen@localhost:~/$ 
```

This command shows the sizes of the sections that are discussed above. The text, data and bss sections are 1516, 600, and 8 bytes. In total this sums up to 2124 bytes, which can be written hexadecimally as 0x84C.

OK, this makes sense :)

## 3.1.2 Run task !

By the time you're reading this part of the course, running the binary that was compiled above should be a walk in the park.

```bash
jvliegen@localhost:~/$ ./eg3_1
hello world !

jvliegen@localhost:~/$ 
```

When a program is started, an **instance** of the program is created. This results (among many other things) in an assignment of the instance in the memory. This means that the program is mapped somewhere in the memory space.