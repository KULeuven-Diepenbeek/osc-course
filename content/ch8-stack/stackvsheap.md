---
title: '8.1: The Stack & the Heap'
pre: "<i class='fas fa-book'></i> "
weight: 1
---

## The Stack and the Heap

### Program Memory

<div>
    <span style="float: left; width: 70%">
        Compiled computer programs are divided into different sections, each with their own specific needs and properties. Together, they form the <strong>program memory</strong>.<br/>
        The following image represents these sections, from bottom to top:

        <ol>
            <li>
                <strong>text</strong><br/>
                Read-only, fixed size. Contains executable instructions.
            </li>
            <li>
                <strong>data</strong><br/>
                Can be modified. Contains global or static variables that are initialized, such as <code>static int i = 5;</code>. Global variables are variables that live outside of any function scope, and are accessible everywhere, such as <code>int i = 5; int main() { printf("%d", i); }</code>. See <a href="/ch8-stack/scope/">Section 8.3</a>.
            </li>
            <li>
                <strong>bss</strong><br/>
                Can be modified. Contains <em>uninitialized</em> data, such as <code>static int i;</code>.
            </li>
            <li>
                <strong>heap</strong><br/>
                Dynamically growing. Contains data maintained by <code>malloc()</code> and <code>free()</code>, meaning most pointer variables. The heap is shared by all threads, shared librarys, and dynamically loaded modules in a process. Can be modified while the process is running. 
            </li>
            <li>
                <strong>stack</strong><br/>
                Set size. Contains <em>automatic variables</em>: variables created when (automatically) entered a function, such as <code>int main() { int i = 5; }</code>. Can be modified manually using the command <code>ulimit</code> - but this cannot be modified once the process is running. 
            </li>
        </ol>
    </span>
    <span style="float: right; width: 30%">
        <img src="/img/Program_memory_layout.pdf.jpg" title="Source: Wikipedia" />
    </span>
</div>
<div style="clear: both;">&nbsp; </div>

### The Stack

Besides (automatic) variables, a few more important things also live in the stack section of the program. These are the **stack pointer** (SP) and the 'program stack' itself. 

Contrary to initialized pointers, **statically sized** arrays within functions are also bound to the stack, such as `char line[512];`. This is an important distinction, since those same arrays are translated into pointers when passing through functions! You can easily remember the difference by looking at the size: if it's `var[XX]`, then it's a stack variable - even if XX is not a literal but a computed value. 

### The Heap

Contrary to arrays, initialized pointers are bound to the heap, such as `char* line = malloc(sizeof(char) * 10)` - _except for_ pointer values that are being assigned directly with a string constant such as `char* line = "hello";`. Freeing the last line would result in the error _munmap\_chunk(): invalid pointer_. 

The usage of `malloc()` and such is required if you want to reserve space on the heap. [memcpy()](https://www.tutorialspoint.com/c_standard_library/c_function_memcpy) from `<string.h>` makes it possible to copy values from the stack to the heap, without having to reassign every single property. Make sure to reserve space first!

```C
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Data {
    int one;
    int two;
} Data;

Data* from_stack() {
    Data data = { 1, 2 };
    Data *heap_data = malloc(sizeof(Data));
    memcpy(heap_data, &data, sizeof(Data));
    return heap_data;
}

int main() {
    Data* heap = from_stack();
    printf("one: %d, two: %d\n", heap->one, heap->two);
}
```

This is called creating a **deep copy**, while a **shallow copy** creates a copy of a pointer, still pointing to the same value in memory space.

{{% task %}}
What happens when you omit `malloc()` and simply write `Data *heap_data = memcpy(heap_data, &data, sizeof(Data));`?
{{% /task %}}

As another side node, it is possible to resize variables on the heap, using `realloc()`. This is simply not possible on the stack: they cannot be resized. Also, using [calloc](https://www.tutorialspoint.com/c_standard_library/c_function_calloc.htm) instead of malloc initializes the allocated memory to zero instead of "nothing". So now you know how to use `malloc`, `calloc`, `realloc`, and `free`.

### Inspecting program memory in the OS

Unix-like operating systems implement [procfs](https://en.wikipedia.org/wiki/Procfs), a special filesystem mapped to `/proc`, that makes it easy for us to inspect program running program state. You will need the process ID (PID) as it is the subdir name. Interesting files to inspect are:

* `/proc/PID/maps`, a text file containing information about mapped files and blocks (like heap and stack).
* `/proc/PID/mem`, a binary image representing the process's virtual memory, can only be accessed by a ptrace'ing process.

We will take a closer look at these during the labs.

Mac OSX Does not have _procfs_. Instead, you will have to rely on commandline tools such as `sysctl` to query process information. 

### Should I use the stack or the heap?

Good question. The answer is obviously **both**. Use the stack when:

* You do not want to de-allocate variables yourself.
* You need speed (space is managed efficiently by the CPU). 
* Variable size is static.

Use the heap when:

* You require a large amount of space (virtually no memory limit).
* You don't mind a bit slower access (fragmentation problems can occur).
* You want to pass on (global) objects between functions. 
* You like managing things yourself.
* Variable size could be dynamic.

What piece of code could be _dynamic_ in size? Data structures, such as linked lists from [chapter 3: pointers and arrays](/ch3-pointers), are a good candidate for this: arrays, sets, maps, and any other form of collection can grow and shrink in size, therefore need dynamic memory mapped. Using `[]` will, in most cases, not suffice in the C programming language, unless you are doing something very simple. 

## Memory management

### Freeing up space

In order to create an instance of a structure and return it, you have to allocate memory using `malloc()` from `<stdlib.h>` - we now that already. In contrast with higher level languages such as Java, C requires programmes to clean up the allocaed memory themselves! This means calling `free()` to free up the space for future use. For instance:

```C
struct Stuff {
    int number;
};
typedef struct Stuff Stuff;

void do_nasty_things() {
    // ...
    Stuff* ugly = malloc(sizeof(Stuff));
    ugly->number = 10;
    // ...
}
int main() {
    do_nasty_things();
    // other things
}
```

As soon as the method `do_nasty_things()` ends, `ugly` is not accessible anymore because it was not returned and there are no other references to it. However, after the function, memory is still reserved for it. To counter **memory leaks** such as these, you can do a few things:

1. Keep things _local_, by keeping things on the stack. The Stack, for that function, will be cleared after calling it. Change `Stuff*` to `Stuff`.
2. Free the pointer space at the end of the function by calling `free(ugly)`.

Since this is a small program that ends after `main()` statements are executed, it does not matter much. However, programs with a main loop that require a lot of work can also contain memory leaks. If that is the case, leak upon leak will cause the program to take op too much memory and simply freeze. 

Do not make the mistake to free up stack memory, such as in this nice example, from the '[Top 20 C pointer mistakes](https://www.acodersjourney.com/top-20-c-pointer-mistakes/)':

```C
int main() {
  int* p1;
  int m = 100;  // stack var
  p1 = &m;      // pointer to stack var

  free(p1);     // BOOM headshot!
  return 0;
}
```

<pre>
a.out(83471,0x7fff7e136000) malloc: *** error for object 0x7fff5a24046c: pointer being freed was not allocated
*** set a breakpoint in malloc_error_break to debug
Abort trap: 6    
</pre>

{{% task %}}
Let's try and write a program that gradually increases heap memory consumption by `malloc()`-ing inside a never-ending loop. For brevity, add `sleep(1)` in-between calls (include from `#include <unistd.h>`). Can you see this in increase in your task manager?
{{% /task %}}

Some operating systems provide easy to use sampling tools, such as MacOS' sampler. Go to Activity Monitor, rightclick on a process and choose "sample". The above task outputs:

<pre>
Date/Time:       2021-04-18 20:18:48.499 +0200
Launch Time:     2021-04-18 20:18:22.379 +0200
OS Version:      macOS 11.2 (20D5042d)
Report Version:  7
Analysis Tool:   /usr/bin/sample

Physical footprint:         977K
Physical footprint (peak):  977K
----

Call graph:
    2891 Thread_357865   DispatchQueue_1: com.apple.main-thread  (serial)
      2891 start  (in libdyld.dylib) + 4  [0x1a2999f34]
        2891 main  (in a.out) + 24  [0x10445bf08]
          2891 sleep  (in libsystem_c.dylib) + 48  [0x1a28c2184]
            2891 nanosleep  (in libsystem_c.dylib) + 216  [0x1a28c23a0]
              2891 __semwait_signal  (in libsystem_kernel.dylib) + 8,16  [0x1a2948284,0x1a294828c]

Total number in stack (recursive counted multiple, when >=5):

Sort by top of stack, same collapsed (when >= 5):
        __semwait_signal  (in libsystem_kernel.dylib)        2891
</pre>

The stack sample is clearly visible, but the heap is not. 

### Dangling pointers

A second mistake could be that things _are_ indeed being freed, but pointers still refer to the freed up space, which is now being rendered invalid. This is called a **dangling pointer**, and can happen both on the heap (while _dereferencing_ an invalid pointer after freeing up space):

```C
int *p, *q, *r;
p = malloc(8);
// ...
q = p;
// ...
free(p);
r = malloc(8);
// ...
something = *q; // aha! 
```

, and on the stack (while _dereferencing_ an invalid pointer after returning an address to a local variable that gets cleaned up because it resides on the stack):

```C
int *q;
void foo() {
    int a;
    q = &a;
}
int main() {
    foo();
    something = *q; // aha!
}
```

### Garbage Collection - not happening in C...

The above mistakes are easily made if you are used to Java:

```java
void foo() {
    Animal cow = new Animal();
    cow.eat();
    // ...
}
public static void main(String[] args) {
    foo();
    // cow instances are cleaned up for you...
}
```

This cleaning process, that automatically frees up space in multiple parts of the allocated memory space, is called **garbage collecting**. <br/>
And it is completely _absent_ in C, so beware!

### What happens when the stack and heap collide?

That is **platform-dependent** and will hopefully crash instead of cause all forms of pain. There are a few possibilities:

1. Stack --> heap. The C compiler will silently overwrite the heap datastructure! On modern OS systems, there are **guard pages** that prevent the stack from growing, resulting in a _segmentation fault_. Also, modern compilers throw exceptions such as **stack overflow** if you attempt to go outside the reserved space (= segfault). 
2. Heap --> Stack. The `malloc()` implementation will notice this and return `NULL`. It is up to you to do something with that result. 

{{% task %}}
Write a program with an infinite loop that puts stuff on the stack. What is the program output?<br/>
Do the same with infinite malloc()'s. What happens now?
{{% /task %}}

### What's a stack overflow?

The stack is a limited, but fast piece of program memory, made available for your program by the OS. The keyword here is **limited**. Unlike the heap, it will not dynamically grow, and it is typically hard-wired in the OS. Simply keeping on adding stuff to the stack, such as calling methods within methods without a stop condition (infinite recursion), will cause a stack overflow exception, signaling that the OS prevented your program from taking over everything:

```c
// forward definition
void flow();

void flow() {  // on the stack
    int x = 5; // on the stack
    flow();    // keep on going
}

int main() {
    flow();
}
```

This causes a _segmentation fault_, signaling that it was killed by the OS. Add `printf()` statements to your liking. 

How do I know how big the stack can be on my OS? Use `ulimit -a` to find out: (Executed on a 2012 MacBbook Air)

<pre>
outers-MacBook-Air:ch8-stack wgroeneveld$ ulimit -a
core file size          (blocks, -c) 0
data seg size           (kbytes, -d) unlimited
file size               (blocks, -f) unlimited
max locked memory       (kbytes, -l) unlimited
max memory size         (kbytes, -m) unlimited
open files                      (-n) 4864
pipe size            (512 bytes, -p) 1
stack size              (kbytes, -s) 8192           **BINGO**
cpu time               (seconds, -t) unlimited
max user processes              (-u) 709
virtual memory          (kbytes, -v) unlimited
</pre>

So it's **8.19 MB**. 

Interestingly, the same command outputs something radically different on a 2021 MacBook Air with an ARM64 chipset:

<pre>
➜  osc-course git:(master) ✗ ulimit -a
-t: cpu time (seconds)              unlimited
-f: file size (blocks)              unlimited
-d: data seg size (kbytes)          unlimited
-s: stack size (kbytes)             8176
-c: core file size (blocks)         0
-v: address space (kbytes)          unlimited
-l: locked-in-memory size (kbytes)  unlimited
-u: processes                       1333
-n: file descriptors                256
</pre>

Although the stack size stays more or less the same, the max processes number dramatically increased. Yay for technological advances!

{{% task %}}
Check your stack limit with `ulimit`. Write a program that blows up the stack using statically sized arrays by defining more than the applied limit. Which data type did you pick? How big is your array? Why?
{{% /task %}}


## Optimizing C code

#### Compiler flags

Depending on your compiler and your target platform, the C compiler will try to optimize code by rearranging declarations and possibly even removing lines such as completely unused variables. The GNU and LLVM `gcc` compilers offer multiple levels of optimization that can be enabled by passing along `-O1`, `-O2`, and `-O3` flags (O = Optimize). Consider the following code:

```C
#include <stdio.h>
#include <stdlib.h>
void stuff() {
    char dingdong[] = "hello? who's there?";
    printf("doing things\n");
}
int main() {
    stuff();
}
```

`stuff` is not doging anything with the char array. Compile with `gcc -g -O3 test.c` to enable debug output and optimize. When disassembling using `lldb` (LLVM) or `gdb` (GNU), we see something like this:

<pre>
(lldb) disassemble --name stuff
a.out`stuff at test.c:3:
a.out[0x100000f30]:  pushq  %rbp
a.out[0x100000f31]:  movq   %rsp, %rbp
a.out[0x100000f34]:  leaq   0x4b(%rip), %rdi          ; "doing things"
a.out[0x100000f3b]:  popq   %rbp
a.out[0x100000f3c]:  jmp    0x100000f64               ; symbol stub for: puts

a.out`main + 4 [inlined] stuff at test.c:12
a.out`main + 4 at test.c:12:
a.out[0x100000f54]:  leaq   0x2b(%rip), %rdi          ; "doing things"
a.out[0x100000f5b]:  callq  0x100000f64               ; symbol stub for: puts
a.out[0x100000f60]:  xorl   %eax, %eax
</pre>

Where is `dingdong`? The compiler saw it was not used and removed it. Without the `-O3` flag:

<pre>
(lldb) disassemble --name stuff
a.out`stuff at test.c:3:
a.out[0x100000e90]:  pushq  %rbp
a.out[0x100000e91]:  movq   %rsp, %rbp
a.out[0x100000e94]:  subq   $0x30, %rsp
a.out[0x100000e98]:  movq   0x171(%rip), %rax         ; (void *)0x0000000000000000
a.out[0x100000e9f]:  movq   (%rax), %rax
a.out[0x100000ea2]:  movq   %rax, -0x8(%rbp)
a.out[0x100000ea6]:  movq   0xc3(%rip), %rax          ; "hello? who's there?"
a.out[0x100000ead]:  movq   %rax, -0x20(%rbp)
a.out[0x100000eb1]:  movq   0xc0(%rip), %rax          ; "ho's there?"
a.out[0x100000eb8]:  movq   %rax, -0x18(%rbp)
a.out[0x100000ebc]:  movl   0xbe(%rip), %ecx          ; "re?"
a.out[0x100000ec2]:  movl   %ecx, -0x10(%rbp)
a.out[0x100000ec5]:  movl   $0x0, -0x24(%rbp)
a.out[0x100000ecc]:  cmpl   $0xa, -0x24(%rbp)
a.out[0x100000ed3]:  jge    0x100000ef2               ; stuff + 98 at test.c:5
a.out[0x100000ed9]:  movslq -0x24(%rbp), %rax
a.out[0x100000edd]:  movb   $0x63, -0x20(%rbp,%rax)
a.out[0x100000ee2]:  movl   -0x24(%rbp), %eax
a.out[0x100000ee5]:  addl   $0x1, %eax
a.out[0x100000eea]:  movl   %eax, -0x24(%rbp)
a.out[0x100000eed]:  jmp    0x100000ecc               ; stuff + 60 at test.c:5
a.out[0x100000ef2]:  leaq   0x8b(%rip), %rdi          ; "doing things\n"
a.out[0x100000ef9]:  movb   $0x0, %al
a.out[0x100000efb]:  callq  0x100000f46               ; symbol stub for: printf
a.out[0x100000f00]:  movq   0x109(%rip), %rdi         ; (void *)0x0000000000000000
a.out[0x100000f07]:  movq   (%rdi), %rdi
a.out[0x100000f0a]:  cmpq   -0x8(%rbp), %rdi
a.out[0x100000f0e]:  movl   %eax, -0x28(%rbp)
a.out[0x100000f11]:  jne    0x100000f1d               ; stuff + 141 at test.c:9
a.out[0x100000f17]:  addq   $0x30, %rsp
a.out[0x100000f1b]:  popq   %rbp
a.out[0x100000f1c]:  retq
a.out[0x100000f1d]:  callq  0x100000f40               ; symbol stub for: __stack_chk_fail
</pre>

You can fiddle with options and such yourself in [godbolt.org](https://godbolt.org/).

{{% notice note %}}
Instead of bootstrapping the debugger to inspect disassembly, you can also simply dump the object contents using `objdump -D` (GNU) or `otool -tV` (OSX).
{{% /notice %}}

#### volatile

When heavily optimizing, sometimes you do not want the compiler to leave things out. This is especially important on embedded devices with raw pointer access to certain memory mapped spaces. In that case, use the `volatile` keyword on a variable to tell the compiler to "leave this variable alone" - do not move it's declaration and do not leave it out. [For instance](https://godbolt.org/z/Dm5YHx):

```C
int array[1024];
int main (void) {
    int  x;

    for (int i = 0; i < 1024; i++) {
        x = array[i];
    }
}
```

Does pretty much nothing. Compiling with `-O3` results in 2 assembly instructions: 

<pre>
main:
  xor eax, eax
  ret
</pre>

However, if you want `x` to be left alone, use `volatile int x;` and recompile:

<pre>
main:
  mov eax, OFFSET FLAT:array
.L2:
  mov edx, DWORD PTR [rax]
  add rax, 4
  mov DWORD PTR [rsp-4], edx
  cmp rax, OFFSET FLAT:array+4096
  jne .L2
  xor eax, eax
  ret
</pre>

That's a big difference. 

#### Function call order

Another part of optimizing code is the determination of function call order. For instance, consider the following statement: `x = f() + g() * h()`. Which function gets called first? 

The answer is **we do not know**. Do _not_ rely on function order to calculate something! Each function should be completely independant. There should not be a global variable manipulated in `f()` which will then be needed in `g()` or `h()`. You can inspect disassembled code for different compilers on [https://godbolt.org/](https://godbolt.org/). It will differ from platform to platform, and from compiler to compiler (and even from option flag to flag). 
