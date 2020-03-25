---
title: '8.2: Inspecting memory regions'
pre: "<i class='fas fa-vial'></i> "
weight: 2
---

Accompanying Screencast:

{{< vimeo 400606180 >}}

## 1. No malloc, no heap

Let's look at memory regions of a process that does not call `malloc()`. 
This means we will not use the heap just yet. Compile the following code:

```c
#include <stdlib.h>
#include <stdio.h>

int main() {
    getchar();  // breaks process until char input
    return 0;
}
```

To explore the above example, we will introduce `getchar()` before ending the `main()` loop, so the program pauses and gives us a change to look under the hood. 

{{% task %}}
Inspect the memory regions of the above program while running it. Look up the process ID using `ps aux` and browse through the files using `cat` in `/proc/[procid]`.
{{% /task %}}

Locate the following:

<pre>
7f8122192000-7f8122193000 rw-p 00000000 00:00 0 
7fffc566a000-7fffc568b000 rw-p 00000000 00:00 0                          [stack]
7fffc577d000-7fffc5780000 r--p 00000000 00:00 0                          [vvar]
7fffc5780000-7fffc5782000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
</pre>

No `[heap]` region allocated yet. Let's do the same, but use `malloc()` to allocate a random block of memory. The return value of the method is a `void*` that can be printed to show the address of the heap region. Use `printf("%p", p)`.

## 2. malloc: use heap

{{% task %}}
Extend the above example and allocate dynamic memory. What happens in the `/proc` files? Can you see how the returned address is inside the heap region?
{{% /task %}}

Let us use the program `strace` to figure out what `malloc()` exactly does. It should be a system call that asks the Operating System to allocate a certain amount of dynamic memory. But we have yet to figure out **which system calls** exactly are called. The program `strace` is used to track system calls and signals. Don't be surprised by the amount of calls a simple program like ours makes! Let us try to find the calls for memory allocation.

It is a good idea to `printf("before malloc! ")` to make sense of the `strace` output.

{{% task %}}
use `strace ./program`. It will output a lot of text, ending with `read(0,` (that is our `getchar()` break). Can you find the syscalls we are after?
{{% /task %}}

<pre>
munmap(0x7f88a38dc000, 114791)          = 0
brk(NULL)                               = 0x5644fb34d000
brk(0x5644fb36e000)                     = 0x5644fb36e000
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 1), ...}) = 0
write(1, "0x5644fb34d260\n", 150x5644fb34d260
)        = 15
fstat(0, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 1), ...}) = 0
read(0,
</pre>

Aha, `brk`! What is that? Use `man brk` to find out more. 

The data segment gets expanded by moving the _program break_ pointer up, so the heap is actually an extension of the data segment of the program. 

## 3. multiple mallocs

What happens when we call `malloc()` multiple times in a row? 

{{% task %}}
Extend the program by allocating `1024` bytes four times in a row. Inspect the program again using `strace`. What do you notice?
{{% /task %}}

Memory allocation is optimized by avoiding a system call each time. It firsts allocates more than needed that will (hopefully) suffice. 

Instead of calling malloc four times, let's see what happens when we use a loop to see how many times `brk` is called. More importantly, we will also see that he heap **grows 'upward'**! 

{{% task %}}
Extend the program by allocating `1024` bytes in a for loop (Use `getchar()` before and after the loop) that counts to a random high number. Print "loop" and "end" before and after the loop. Inspect again using the trace tool, and also take a look at the maps file in the process folder. After entering a key you can re-inspect everything.
{{% /task %}}

- Before loop: `556a1a947000-556a1a968000 rw-p 00000000 00:00 0                          [heap]`
- After loop: `556a1a947000-556a1aa4f000 rw-p 00000000 00:00 0                          [heap]`

Converted to decimal: 93914201911296 - 93914200965120 = 946176 bytes used.

Indeed, the Figure from [chapter 7.1](/ch7-stack/stackvsheap) and our findings confirm that the heap grows upwards. 

## 4. Free

Until now the above examples have never taken into consideration the fact that one has to get rid unused space using `free()`. We will leave it up to you to inspect what happens in `/proc`. 

## Extra: Using Valgrind to inspect the memory heap

![](/img/valgrind.png)

Valgrind is a useful commandline tool that makes it easy for C programmers to inspect how much dynamic (heap) memory a program actually consumed, and how much of it was freed. It is a lot easier to use than dabbling in different disassemble commands, but it does NOT come with the GNU toolchain. Use `apt-get install valgrind` to install it onto your virtual machine. 

Let's assume a simple program that reserves some memory, fills in the blanks, and then frees up some space: (also available in the `osc-exercises` repository)

```c
#include <stdlib.h>

int main() {
    int* ptr;
    ptr = malloc(sizeof(int) * 1000);
    // we allocated 4000 bytes (since an int is usually 4 bytes)

    free(ptr);
    return 0;
}
```

After compiling this, we can let the tool figure out how much space we took up, how many leaks there were, and much more:

<pre>
Wouters-MacBook-Air:ch8-stack wgroeneveld$ valgrind ./a.out
==87742== Memcheck, a memory error detector
==87742== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==87742== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==87742== Command: ./a.out
==87742==
--87742-- run: /usr/bin/dsymutil "./a.out"
warning: no debug symbols in executable (-arch x86_64)
==87742==
==87742== HEAP SUMMARY:
==87742==     in use at exit: 22,529 bytes in 188 blocks
==87742==   total heap usage: 268 allocs, 80 frees, 32,649 bytes allocated
==87742==
==87742== LEAK SUMMARY:
==87742==    definitely lost: 3,472 bytes in 55 blocks
==87742==    indirectly lost: 2,832 bytes in 9 blocks
==87742==      possibly lost: 0 bytes in 0 blocks
==87742==    still reachable: 0 bytes in 0 blocks
==87742==         suppressed: 16,225 bytes in 124 blocks
==87742== Rerun with --leak-check=full to see details of leaked memory
==87742==
==87742== For lists of detected and suppressed errors, rerun with: -s
==87742== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
</pre>

{{% task %}}
Try to let the above program produce a few memory leaks. Does valgrind notice you did not clean up your mess? The _definitely lost_ amount should skyrocket after a few uncleaned `malloc()` calls. Are amount of reported bytes correct? Recalculate this manually. 
{{% /task %}}


## Further Reading

- [Hack the Virtual Memory: malloc, the heap & the program break](https://blog.holbertonschool.com/hack-the-virtual-memory-malloc-the-heap-the-program-break/
)
- [Valgrind quickstart](http://valgrind.org/docs/manual/QuickStart.html)