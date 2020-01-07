---
title: '4.2: Debugging using GDB'
pre: "<i class='fas fa-vial'></i> "
weight: 2
---

## 2. The hard way: Command-line debugging using GDB

In order to fluently debug binary programs, they have to be compiled with the **debug flag**, `gcc -g`. This will add metadata to the binary file that gdb uses when disassembling and setting breakpoints. IDEs automatically add metadata like this when you press the "Debug" button on them, but since this is a command-line application, we need to do everything ourselves. 

Let's start with a heap-based application we would like to inspect:

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char password[] = "250382";

int main(int argc, char *argv[])
{
  int stackvar = 5;
  char *buf = (char *)malloc(100);
  char *secret = (char *)malloc(100);

  strcpy(secret, password);

  printf("Crackme! \n");
  printf("Password? ");

  scanf("%s", buf);

  if (!strcmp(buf, secret)) {
    printf("Password OK :)\n");
  } else {
    printf("Invalid Password! %s\n", buf);
  }

  return 0;
}
```

If the source code would not have been supplied, making an estimated guess against the password would take a (very) long time. (We naively assume here that the program has been compiled with debug information enabled).

Compile using `gcc -g hackme.c`. Take a look at the filesize - without flag:

<pre>
wouter@wouter-Latitude-7490:~/Development$ gcc hackme.c -o hackme.bin && ls -la | grep hackme.bin
-rwxr-xr-x  1 wouter wouter 8568 Jan  7 19:59 hackme.bin
</pre>

With flag:

<pre>
wouter@wouter-Latitude-7490:~/Development$ gcc hackme.c -g -o hackme.bin && ls -la | grep hackme.bin
-rwxr-xr-x  1 wouter wouter 11352 Jan  7 19:59 hackme.bin
</pre>

Star the `gdb` debugger using `gdb [binary]`. It will enter the interactive gdb shell, where you can set breakpoints, step through code, and have a chance at inspecting the heap, where we might attempt to figure out what's hidden in there. 

Things you need to know from the GDB debugger:

1. `r`: running the program (main() method execution)
2. `c`: continue after a breakpoint
3. `i`: inspect (`i r [regname]`: inspect register name)
4. `start` and `next`: start stepping through the application.
5. `b *[addr]`: set breakpoint at certain address
6. `delete`: deletes all breakpoints
7. `disassemble [fn]`: disassembles functionname (after running)
8. `x/[length][format] [address expr]`: inspect dynamic memory block (see [manual](http://visualgdb.com/gdbreference/commands/x))

{{% task %}}
Bootstrap gdb and step through the whole application. As soon as the stackvar has been evaluated, try to inspect the memory value using `x/d`. The address expression could be hexadecimal, or `&stackvar`. <br/>
How could you evaluate a heap variable using the x command? If you have the address, how do you pry out the value on the heap? 
{{% /task %}}

Do not forget that the expression that is printed out is the one to be evaluated after you enter the 'next' command. You can already inspect the stack variable address but it will contain junk:

<pre>
(gdb) start
Temporary breakpoint 1 at 0x7d9: file hackme.c, line 11.
Starting program: /home/wouter/Development/hackme.bin 

Temporary breakpoint 1, main (argc=1, argv=0x7fffffffdd68) at hackme.c:11
11    int stack = 5;
(gdb) x/d &stack
0x7fffffffdc6c: 21845
(gdb) next
12    char *buf = (char *)malloc(100);
(gdb) x/d &stack
0x7fffffffdc6c: 5
</pre>

Address `0x7fffffffdc6c` first contains 21845 - a coincidence that might have another value on your machine.

{{% task %}}
Bootstrap gdb, disassemble the `main` function, and set breakpoints after each `malloc()` call using `b *[address]`. You can check the return value, stored at the register eax, with `i r eax`.
{{% /task %}}

Looking at the memory block returned by `malloc()`, 


## Recommended Reading

- [Hackme: exploiting heap bugs](https://tc.gtisc.gatech.edu/cs6265/2016/l/lab10-heap/README-tut.txt
)