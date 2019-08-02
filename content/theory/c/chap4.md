---
title: '4: The Stack & the Heap'
---

Stack, heap, by-value VS by-reference

todo 

* objdump -D voorbeeld
* compiler optimization heavy, unpredictable, ...

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
                Can be modified. Contains global or static variables that are initialized, such as <code>static int i = 5;</code>. Global variables are variables that live outside of any function scope, and are accessible everywhere, such as <code>int i = 5; int main() { printf("%d", i); }</code>. 
            </li>
            <li>
                <strong>bss</strong><br/>
                Can be modified. Contains <em>uninitialized</em> data, such as <code>static int i;</code>.
            </li>
            <li>
                <strong>heap</strong><br/>
                Dynamically growing. Contains data maintained by <code>malloc()</code> and <code>free()</code>, meaning most pointer variables. The heap is shared by all threads, shared librarys, and dynamically loaded modules in a process. 
            </li>
            <li>
                <strong>stack</strong><br/>
                Dynamically growing. Contains <em>automatic variables</em>: variables created when (automatically) entered a function, such as <code>int main() { int i = 5; }</code>.
            </li>
        </ol>
    </span>
    <span style="float: right; width: 30%">
        <img src="/img/Program_memory_layout.pdf.jpg" />
    </span>
</div>
<div style="clear: both;">&nbsp; </div>

### The Stack

Besides (automatic) variables, a few more important things also live in the stack section of the program. These are the **stack pointer** (SP) and the 'program stack' itself. 

Contrary to initialized pointers, arrays within functions are also bound to the stack, such as `char line[512];`.

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

{{% ex %}}
What happens when you omit `malloc()` and simply write `Data *heap_data = memcpy(heap_data, &data, sizeof(Data));`?
{{% /ex %}}

### Inspecting program memory in the OS

Unix-like operating systems implement [procfs](https://en.wikipedia.org/wiki/Procfs), a special filesystem mapped to `/proc`, that makes it easy for us to inspect program running program state. You will need the process ID (PID) as it is the subdir name. Interesting files to inspect are:

* `/proc/PID/maps`, a text file containing information about mapped files and blocks (like heap and stack).
* `/proc/PID/mem`, a binary image representing the process's virtual memory, can only be accessed by a ptrace'ing process.

We will take a closer look at these during the [labs](/practice/lab4).

Mac OSX Does not have _procfs_. Instead, you will have to rely on commandline tools such as `sysctl` to query process information. 

### Should I use the stack or the heap?

Good question. The answer is obviously **both**. Use the stack when:

* You do not want to de-allocate variables yourself.
* You need speed (space is managed efficiently by the CPU). 

Use the heap when:

* You require a large amount of space (virtually no memory limit).
* You don't mind a bit slower access (fragmentation problems can occur).
* You want to pass on (global) objects between functions. 
* You like managing things yourself.

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

```Java
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

{{% ex %}}
Write a program with an infinite loop that puts stuff on the stack. What is the program output?<br/>
Do the same with infinite malloc()'s. What happens now?
{{% /ex %}}
