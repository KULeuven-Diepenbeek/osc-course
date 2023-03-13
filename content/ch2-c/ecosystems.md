---
title: '2.5: C Ecosystems'
pre: "<i class='fas fa-book'></i> "
weight: 5
---

### Separation of concerns: functions in different C files

To make the division clearer, we prepare the following C code, split into two different files:

File `hello.c`:

```C
// hello.c
char* hello() {
    return "heykes";
}
```

File `main.c`:

```C
// main.c
#include <printf.h>
int main() {
    printf("%s", hello());
    return 0;
}
```

The main function has no knowledge of `hello()` because it lives in a different source file. This will be fine if we link the machine code together after compiling. compiling main.c separately gives this:

<pre>
Wouters-MacBook-Air:cmake-build-debug wgroenev$ gcc -c main.c
main.c:5:18: warning: implicit declaration of function 'hello' is invalid in C99
      [-Wimplicit-function-declaration]
    printf("%s", hello());
                 ^
1 warning generated.
</pre>

It is a **WARNING** - not an **ERROR** - so it still compiles! Wow! That is thanks to the `-c` flag (compile only). The warning is easily solved with a **forward function declarations** before the main function: `char* hello ();`. This is the crucial difference between declaration and definition. However, the problems are not yet solved if we want to link this without hello.c:

<pre>
Wouters-MacBook-Air:cmake-build-debug wgroenev$ gcc main.o
Undefined symbols for architecture x86_64:
  "_hello", referenced from:
      _main in main.o
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
</pre>

Okay, so now a blocking **ERROR** was generated. We also need the hello.o binaries to arrive at a successful working program. For that, we first have to execute `gcc -c hello.c` and then` gcc main.o hello.o -o hey`.

With the UNIX tool `nm` we can view the addresses that the linker needs to arrive at the `hey` executable. Try opening hello.o with a text editor. You then see something like this:

<pre>
cffa edfe 0700 0001 0300 0000 0100 0000
0300 0000 f001 0000 0020 0000 0000 0000
1900 0000 8801 0000 0000 0000 0000 0000
0000 0000 0000 0000 0000 0000 0000 0000
7800 0000 0000 0000 1002 0000 0000 0000
7800 0000 0000 0000 0700 0000 0700 0000
0400 0000 0000 0000 5f5f 7465 7874 0000
0000 0000 0000 0000 5f5f 5445 5854 0000
0000 0000 0000 0000 0000 0000 0000 0000
0d00 0000 0000 0000 1002 0000 0400 0000
8802 0000 0100 0000 0004 0080 0000 0000
0000 0000 0000 0000 5f5f 6373 7472 696e
6700 0000 0000 0000 5f5f 5445 5854 0000
0000 0000 0000 0000 0d00 0000 0000 0000
0700 0000 0000 0000 1d02 0000 0000 0000
0000 0000 0000 0000 0200 0000 0000 0000
0000 0000 0000 0000 5f5f 636f 6d70 6163
745f 756e 7769 6e64 5f5f 4c44 0000 0000
0000 0000 0000 0000 1800 0000 0000 0000
2000 0000 0000 0000 2802 0000 0300 0000
9002 0000 0100 0000 0000 0002 0000 0000
0000 0000 0000 0000 5f5f 6568 5f66 7261
6d65 0000 0000 0000 5f5f 5445 5854 0000
0000 0000 0000 0000 3800 0000 0000 0000
4000 0000 0000 0000 4802 0000 0300 0000
0000 0000 0000 0000 0b00 0068 0000 0000
0000 0000 0000 0000 0200 0000 1800 0000
9802 0000 0400 0000 d802 0000 2400 0000
0b00 0000 5000 0000 0000 0000 0200 0000
0200 0000 0200 0000 0400 0000 0000 0000
0000 0000 0000 0000 0000 0000 0000 0000
0000 0000 0000 0000 0000 0000 0000 0000
0000 0000 0000 0000 0000 0000 0000 0000
5548 89e5 488d 0500 0000 005d c368 6579
6b65 7300 0000 0000 0000 0000 0000 0000
0d00 0000 0000 0001 0000 0000 0000 0000
0000 0000 0000 0000 1400 0000 0000 0000
017a 5200 0178 1001 100c 0708 9001 0000
2400 0000 1c00 0000 a8ff ffff ffff ffff
0d00 0000 0000 0000 0041 0e10 8602 430d
0600 0000 0000 0000 0700 0000 0000 001d
0000 0000 0100 0006 1200 0000 0e02 0000
0d00 0000 0000 0000 1900 0000 0e04 0000
3800 0000 0000 0000 0100 0000 0f01 0000
0000 0000 0000 0000 0800 0000 0f04 0000
5000 0000 0000 0000 005f 6861 6c6c 6f00
5f68 616c 6c6f 2e65 6800 4c5f 2e73 7472
0045 485f 6672 616d 6530 0000
</pre>

Beautiful, but not very clear. `nm` does help some:

<pre>
Wouters-MacBook-Air:cmake-build-debug wgroenev$ nm main.o
0000000000000060 s EH_frame0
0000000000000037 s L_.str
                 U _hello
0000000000000000 T _main
0000000000000078 S _main.eh
                 U _printf
Wouters-MacBook-Air:cmake-build-debug wgroenev$ nm hello.o
0000000000000038 s EH_frame0
000000000000000d s L_.str
0000000000000000 T _hello
0000000000000050 S _hello.eh
</pre>

You can see that in main.o the function `_hello` is assigned an **unknown address** (hence the U). This means that the left hand should assume that it is yet to come - and luckily it is correctly defined in hello.o at address `0000000000000000` (there is only 1 function).

{{% notice note %}}
Note that both .o files have overlapping "address spaces": both `_hello` and `_main` are at address `0000000000000000`; this is normal. The linker will properly change/offset these addresses when creating the final program so they no longer overlap. 
{{% /notice %}}

This is the way the files will be coupled to each other:

{{<mermaid>}}
graph TD
    A[hello.c]
    B[main.c]
    C>hello.o]
    D>main.o]
    E{hey executable}
    E --> C
    E -->|"search main() via linker"|D
    C --> A
    D --> B
    D -.->|"search hello() via linker"|C
{{< /mermaid >}}

Functions that have been declared in other source files must therefore be redefined (possibly with the `external` keyword) in your own source file where you wish to use the function. This way the compiler knows that there is a function with that signature, but "he will still come across it". This will be further elaborated in the next labs.

## Compiling everything

We use the UNIX GNU `gcc` compiler to compile C source files and convert them into binaries. The simplest possible way to do so is:

> `gcc *.c`

Due to the lack of a target file name, the compiler creates an "a.out" file that you can execute (`chmod +x` has already been done for you). You can specify this with the "-o" flag. If you have something more to link, put everything in a row one after the other.

However, there are still a lot of compiler options that are [explained at gcc.gnu.org](https://gcc.gnu.org/onlinedocs/gcc/C-Dialect-Options.html) that you can play with.

{{% notice note %}}
When targeting another platform, you will need a **cross-compiler** that compiles on your computer for another computer. That is, the instruction set might differ! (64 or 32-BIT, RISC/ARM, ...)<br/>
Instead of using the default GCC compiler: `gcc bla.c`, you will download and install a custom cross-compiler and evoke it the same way: `arm-eabi-none-gcc bla.c`. The Game Boy Advance (GBA) or RaspberryPi for instance have an ARM chip-set and require this cross-compiler. This differs from most x86 chip-sets that leverages `gcc`.
{{% /notice %}}

{{% task %}}
Are you still cross-compiling if you are compiling on an ARM machine yourself, using `gcc`, compiled for that chip-set? What if you compile code on the Raspberry for your laptop?
{{% /task %}}

#### Step 1: compiling

As seen in the above schematic, executing your source code requires the activation of two steps: compiling (1), and linking (2). [C Preprocessor flags](https://en.wikipedia.org/wiki/C_preprocessor) get parsed just before compiling. Simply calling the `gcc` compiler executes all steps at once. Only compiling is done using the `-c` statement (source input) and providing the source files as arguments, producing **object files**, which can be then linked into a binary.

#### Step 2: linking

After obtaining object files it is simply a matter of concatenating them ('linking'), to create the native executable binary file, using the `-o` flag and providing the object files as arguments. After linking, inspecting the disassembly (see [chapter 5, debugging](/ch5-debugging) on how to do so in detail) shows the concatenated results. 

### Repeatedly compiling

#### (1) using a script

It is annoying to have to type the same command all the time, so a simple alternative is to put your `gcc` command in a shell script:

```sh
#!/bin/sh
clear && gcc -o mystuff source.c && ./mystuff
```

#### (2) Makefiles

In the C world there is such a thing as a "Makefile" that defines which source files should be compiled, and in which order. This is useful for large applications where an overview must be kept.

With Makefiles you can describe "targets" that perform certain actions for you. For example, cleaning up binaries, compiling and linking, all as a separate step. Stringing steps together is of course also possible.

File `Makefile`:

```
.DEFAULT_GOAL := all

CC=gcc

clean:
    rm -rf *.o
    rm -rf *.out

compile:
    $(CC) -c main.c -o main.o

link:
    $(CC) -o main.out main.o

all: clean compile link
```

Typically, the compiler used is set as a shell variable (CC = gcc). You can see here that compiling (gcc with the -c option does not link) and linking is split into separate make 'actions'. This is not really necessary in our exercises, but shows the organizational strength of Make here.

Executing the above steps can be done using the ``make`` command and a default goal (all), or ``make compile`` for a specific goal (executes the 'compile' steps only).

For more information on the correct Makefile syntax, see the [GNU make](ftp://ftp.gnu.org/old-gnu/Manuals/make-3.79.1/html_chapter/make_2.html) documentation.

{{% task %}}
Create a Makefile that contains two targets: `compile` and `run`. The default target should execute both in sequence. As for what to compile, write a simple program that outputs "hello, (name)". The name is something you ask from the user using the stdio function `gets()`.
{{% /task %}}

#### (3) CMake

As you can judge for yourself from the above Makefile syntax, a typical project build file can get pretty verbose and complicated. Recent attempts to mitigate this have resulted in more modern build systems for C/C++, such as the general-purpose [SCons](https://scons.org/), and [CMake](https://cmake.org/). CMake builds... Makefiles. That means you'll have to execute `cmake`, which generates a `Makefile`, and then `make`. It's a two-step process.

{{<mermaid>}}
graph TD
    cmake[CMake]
    make[Makefiles]
    cmd[gcc & cmdline]
    cmake --> make
    make --> cmd
{{< /mermaid >}}


`CMakeLists.txt` contains instructions to generate a` Makefile`:

<pre>
cmake_minimum_required(VERSION 3.10)
project(my_little_pony)
set(CMAKE_CXX_STANDARD 11)

add_executable(my_little_pony main.cpp biblio.cpp biblio.h animals.cpp animals.h)    
</pre>

A simple CMake file is much easier to read and write than a Makefile. See [CMake tutorial](https://cmake.org/cmake-tutorial/) for more information. CLion manages the `add_executable` arguments for you: adding new files to your project will also automatically add them to the list.

Since CMake builds Makefiles and Makefiles use cmdline to evoke the compiler, you are essentially using high-level tools that use low-level tools. This makes it easier to repeatedly compile bigger projects, instead of calling `gcc file.c` yourself every single time. 


#### (4) IDEs

##### Lightweights

A source file consists of simply plain text. Any text editor is sufficient to write your C program. However, it may be useful to use Sublime Text or Visual Studio Code. These modern powerful editors have built-in auto-completion and build tools.

* [Sublime Text 3 Build Systems en C/C++](https://www.thecrazyprogrammer.com/2017/04/how-to-run-c-and-c-program-in-sublime-text.html) and [docs](http://docs.sublimetext.info/en/latest/file_processing/build_systems.html)
* [Visual Studio Code C/C++ integration](https://code.visualstudio.com/docs/languages/cpp)

We will not stop old-school fans from using Emacs or Vi(m). 

##### Heavyweights

[CLion](https://www.jetbrains.com/clion/) is the perfect cross-platform and cross-compiler candidate to do the heavy C/C++ lifting for you, and it comes with integrated debugging, stack inspection, and everything else you might expect from an IDE. If you are familiar with IntelliJ, you will love CLion: it's built on the same platform (IDEA) - even most shortcuts are the same.

{{% figure src="/img/clion.png" %}}

CLion is not free, but it is highly recommended for students (and they get a free license if you register with your university e-mail address). CLion also by default works with CMake. 
