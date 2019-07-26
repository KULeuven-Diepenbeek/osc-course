---
title: 'Chapter x: Introduction of the C ecosystem'
---

&laquo;&nbsp;[Back to Table of Contents](/)<br/>

## The C programming language

The [C language](https://en.wikipedia.org/wiki/C_(programming_language)) is a programming language developed in the '70s to make it easier to interface with hardware. C was/is in essence nothing more than a few abstraction layers on top of assembly itself. 

C is an **imperative** programming language. You will notice this when writing some code yourself: we write instructions as _statements_. These rules or statements are structured in `function` and `struct` types. There is little **declarative** to it, compared to other higher level languages. C's footprint is quite small, the syntax is concise and easy to learn. Statements always express _how_ to do things, instead of _what_ it is doing. Increasing readability is of course important. We could for instance use `#define` to give meaning to a few symbols, or write clear `function` blocks.

C is primarily being used in embedded system development because it is so closely related to the hardware itself. The UNIX, Windows and OSX kernels are fully written in C. The operating system of your cellphone, smartwatch or handheld all build on top of C. A huge amount of languages such as Java (JVM), Python, Ruby and PHP are first and foremost implemented in C.

### Comparison with Java

```java
import java.io.IOException;
import java.nio.*;

class FileReader {

    @Override
    public String read(String file) throws IOException {
        return new String(Files.readAllBytes(Paths.get(file)));
    }
}

class Main {
    public static void main(String[] args) {
        System.out.println("reading file: ");
        System.out.println(new FileReader().read("sup.txt"));
    }
}
```

How would one go around doing something like that in C? That will become difficult as C does not have a `class` system! A lower level implementation could look like this:

```C
#include <stdio.h>
#include <stdlib.h>

char* read(char* file) {
    FILE *filePointer = fopen(file, "r");
    char *buffer = malloc(255);

    fgets(buffer, 255, (FILE*) filePointer);
    fclose(filePointer);
    return buffer;
}

int main() {
    printf("reading file: \n");
    printf("%s\n", read("sup.txt"));
    return 0;
}
```

Compile with `gcc -o fileio fileio.c`.

There are a lot of problems with this implementation: the buffer length is hardcoded and the memory has not been released. A `FileReader` Java class that does everything for you simply cannot be created. As you can see it's a lot more **low-level** work than Java's one-liners like `Files.readAllBytes`! C does not even have the keyword `new`. Ouch.

Key differences between C and a higher level language such as C#:

1. C's syntax footprint is small: no private/protected/class/interface/inheritance/bool/string... No "standard" libraries.
2. C does NOT have exceptions! It works with _interrupts_ and error codes (`return 0`).
3. C does NOT have garbage collection: you manage the memory yourself.
4. C does NOT have a virtual machine (JVM, CLR) but gets compiled to native machine code.
5. C code usually is full of pointer variables to manipulate memory directly.
6. C allows for combination-integer-types (`unsigned short int`)
7. C works with headers (.h) and source (.c) files. An executable file requires two steps: compiling and linking. Linking allows for [mixing with assembly](https://www.devdungeon.com/content/how-mix-c-and-assembly).

## Basic C

### Hello World

```C
#include <stdio.h>

int main() {
    int nr = 42;
    printf("sup? %d", nr);
    return 0;
}
```


The `main()` function returns a number that determines whether or not your program was executed successfully (0), else some kind of error code will be returned. `printf` is a function in the default IO header die we we need to include, just like Java's `import`.

The "f" of printf stands for "formatting" as you can see in the example. See [Formatted output](https://www.gnu.org/software/libc/manual/html_node/Formatted-Output.html).

### Structuring your code

Done with `function`. Blocks such as if, for, while, do are familiar and work just like in other languages:

```C
#include <stdio.h>

void say_something_if_positive(int number) {
    if(number > 5) {
        printf("wow, positive or what? \n");
        for(int i = 1; i <= number; i++) {
            printf("%d ", i);
        }
        printf("\n");
    }
}

int main() {
    say_something_if_positive(5);
    return 0;
}
```

You **cannot overload** functions in C, unlike in C++ and Java. That means each function name is unique.

### Strings? What do you mean?

Forget it: ``char[]`` or a ``char*`` pointer is the only possibility. And no, it is not as easy as in Java to handle arrays due to the way they are defined.

```C
#include <stdio.h>
#define SIZE 10

int main() {
    int arr[SIZE];
    for(int i = 0; i < SIZE; i++) {
        arr[i] = i * 10;
    }

    for(int j = 0; j < SIZE; j++) {
        printf("array index %d has value %d \n", j, arr[j]);
    }

    char string[] = "hi there";
    printf("%s", string);

    return 0;
}

```

C reserves the right amount of memory with string literals you know from Java. The `string[]` char array does contain **9 characters** and not 8! That is because the end of the array is determined by a magical **NULL terminator**, `\0`. That makes it easier to loop through all characters and print them - or just let printf do that for you by formatting using `%s`.

Handy string utility functions reside in the header file `<string.h>` (copying, concatenating, asking for the length, ...) See [GNU C: String utils](https://www.gnu.org/software/libc/manual/html_node/String-and-Array-Utilities.html).

### Structs

The only way to structure data in C is using the `struct` keyword:

```C
struct Person {
    int age;
    int gender;   // geen bool, remember?
    char name[];
}
```

We can use this structure to assign values like this:

```C
struct Person jaak;    // do not forget "struct"
jaak.name = "Jaak Trekhaak";
jaak.age = 80;
jaak.gender = 1;
```

The next question is, can we also define functions in a `struct`? Jes and no. A function pointer makes this possible, but it is not the same such as a member variable of a class in Java. C function pointers, however, can be very usefully used as _callback methods_:

```C
#include <stdio.h>

struct Person {
    int age;
    int (*is_old)();
};

int is_old(struct Person this) {
    printf("checking age of person: %d\n", this.age);
    return this.age > 60;
}

int main() {
    struct Person jaak;
    jaak.age = 40;
    jaak.is_oud = &is_oud;

    printf("is jaak old? %d\n", jaak.is_old(jaak));  
}
```

It looks a bit weird because there is no such thing as a magical variable named `this` - that's one argument you have to provide yourself. You can emulate functions as members of a data structure, but as you can see it's going to cost you. 

### Extra definitions

Creating a person looks awkward: `struct Person jaak;` - why can't we simply use `Person jaak;`? That is possible if you **define** your own types using the keyword `typedef`. It's also useful to emulate your own `string` implementation:

```C
typedef struct Person Person;
typedef char* string;
```

Magic numbers are usually defined on top, in header files, using `#define`. With some tricks we can emulate booleans in C:

```C
#define TRUE 1
#define FALSE 0

typedef unsigned short int bool;

bool male = TRUE;
```


Typical C code that you may encounter due to lack of a bool: `if (result) {...}` where result is an `int`. This is in **no case** the same as [JavaScripts Truthy / Falsey](https://j11y.io/javascript/truthy-falsey/) construction! The number `0` is false. `EOF`,` NULL` or `\ 0` all evaluate to a number to use this.

## Use of header Files

The `#include` statements ensure the correct inclusion of functions in your program. Large programs consist of multiple C (source) and H (header) files that are glued together with compiling and linking. A header file contains function **definitions**, the **declarations** are in the source files:

```
// person.h

struct Person {
    int age;
}
int is_old(struct Person p);
```

With the following source file:

```
// person.c

#include <stdio.h>
#include "person.h"

int is_old(struct Person p) {
    return p.age > 60;
}

int main() {
    struct Person jaak;
    jaak.age = 10;

    return 0;
}
```

The `` main`` function works as a bootstrapper and is never placed in a header file. Note the difference between brackets `<>` and brackets `""` at include: that is the difference between system includes and own includes (use relative paths!).

The reason for splitting this up is that other source files also provide access to `is_old()` and `Person` and thus the ability to reuse things.

{{<mermaid>}}
graph LR;
    A{person.h} -->|source| B[person.c]
    B --> E[definitie is_old]
    A{person.h} -->|source| C[facebook.c]
    C --> F[use struct]
    A{person.h} -->|source| D[twitter.c]
    D --> G[use struct]
{{< /mermaid >}}

### Separation of concerns: functions in different C files

To make the division clearer, we prepare the following C code, split into different files:

```C
// hello.c
char* hello() {
    return "heykes";
}
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
  "_hallo", referenced from:
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
heykesWouters-MacBook-Air:cmake-build-debug wgroenev$ nm hallo.o
0000000000000038 s EH_frame0
000000000000000d s L_.str
0000000000000000 T _hello
0000000000000050 S _hello.eh
Wouters-MacBook-Air:cmake-build-debug wgroenev$ nm main.o
0000000000000060 s EH_frame0
0000000000000037 s L_.str
                 U _hallo
0000000000000000 T _main
0000000000000078 S _main.eh
                 U _printf
</pre>

You can see that in main.o the function `_hello` is assigned an **unknown address** (hence the U). This means that the left hand should assume that it is yet to come - and luckily it is correctly defined in hello.o at address `0000000000000000` (there is only 1 function).

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
    D -.->|"search hallo() via linker"|C
{{< /mermaid >}}

Functions that have been declared in other source files must therefore be redefined (possibly with the `external` keyword) in your own source file where you wish to use the function. This way the compiler knows that there is a function with that signature, but "he will still come across it". This will be further elaborated in the next labs.

## Compiling everything

We use the UNIX GNU `gcc` compiler to compile C soure files and convert them into binaries. The simplest possible way to do so is:

> `gcc *.c`

Due to the lack of a target file name, the compiler creates an "a.out" file that you can execute. You can specify this with the "-o" flag. If you have something more to link, put everything in a row one after the other.

However, there are still a lot of compiler options that are [explained at gcc.gnu.org](https://gcc.gnu.org/onlinedocs/gcc/C-Dialect-Options.html) that you can play with.

### Repeatedly compiling: (1) using a script

It is annoying to have to type the same command all the time, so a simple alternative is to put your gcc command in a shell script:

```sh
#!/bin/sh
clear && gcc -o mystuff source.c && ./mystuff
```

### Repeatedly compiling: (2) Makefiles

In the C world there is such a thing as a "Makefile" that defines which source files should be compiled, and in which order. This is useful for large applications where an overview must be kept.

With Makefiles you can describe "targets" that perform certain actions for you. For example, cleaning up binaries, compiling and linking, all as a separate step. Stringing steps together is of course also possible.

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

### Repeatedly compiling: (3) IDEs

#### Lightweights

A source file consists of simply plain text. Any text editor is sufficient to write your C program. However, it may be useful to use Sublime Text or Visual Studio Code. These modern powerful editors have built-in auto-completion and build tools.

* [Sublime Text 3 Build Systems en C/C++](https://www.thecrazyprogrammer.com/2017/04/how-to-run-c-and-c-program-in-sublime-text.html) and [docs](http://docs.sublimetext.info/en/latest/file_processing/build_systems.html)
* [Visual Studio Code C/C++ integration](https://code.visualstudio.com/docs/languages/cpp)

We will not stop old-school fans from using Emacs or Vi(m). 

#### Heavyweights

[CLion](https://www.jetbrains.com/clion/) is the perfect cross-platform and cross-compiler candidate to do the heavy C/C++ lifting for you, and it comes with integrated debugging, stack inspection, and everything else you might expect from an IDE. If you are familiar with IntelliJ, you will love CLion: it's built on the same platform (IDEA) - even most shortcuts are the same.

<img src="https://brainbaking.com/img/teaching/clion.png" class="bordered" alt="A CLion project" />

CLion is not free, but it is highly recommended for students (and they get a free license if you register with your university e-mail address). CLion works with CMake: `CMakeLists.txt` contains instructions to generate a` Makefile`:

<pre>
cmake_minimum_required(VERSION 3.10)
project(testje)
set(CMAKE_CXX_STANDARD 11)

add_executable(testje main.cpp biblio.cpp biblio.h dieren.cpp dieren.h)    
</pre>

A simple CMake file is much easier to read and write than a Makefile. See [CMake tutorial](https://cmake.org/cmake-tutorial/) for more information. CLion manages the `add_executable` arguments for you: adding new files to your project will also automatically add them to the list.

## <a name="oef"></a>Lab exercises

TODO overnemen of niet?

## Ponder on this

TODO
