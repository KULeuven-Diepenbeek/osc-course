---
title: '2.1: The C programming language'
pre: "<i class='fas fa-book'></i> "
weight: 1
---

The [C language](https://en.wikipedia.org/wiki/C_(programming_language)) is a programming language developed in the '70s to make it easier to interface with hardware. C was/is in essence nothing more than a few abstraction layers on top of assembly itself. 

## A quick intro to C

C is an **imperative** programming language. You will notice this when writing some code yourself: we write instructions as _statements_. These rules or statements are structured in `function` and `struct` types. There is little **declarative** to it, compared to other higher level languages. C's footprint is quite small, the syntax is concise and easy to learn. Statements always express _how_ to do things, instead of _what_ it is doing. Increasing readability is of course important. We could for instance use `#define` to give meaning to a few symbols, or write clear `function` blocks.

C is primarily being used in embedded system development because it is so closely related to the hardware itself. The UNIX, Windows and OSX kernels are fully written in C. The operating system of your cellphone, smartwatch or handheld all build on top of C. A huge amount of languages such as Java (JVM), Python, Ruby and PHP are first and foremost implemented in C.

<iframe height="400px" width="100%" src="https://replit.com/@wgroeneveld1/osc-1-files?lite=true" scrolling="no" frameborder="no" allowtransparency="true" allowfullscreen="true" sandbox="allow-forms allow-pointer-lock allow-popups allow-same-origin allow-scripts allow-modals"></iframe>

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

{{% task %}}
Compile the above with `gcc -o fileio fileio.c`. <br/>
Save some text in a file called "sup.txt", and execute the program with `./fileio`. <br/>
Congratulations on your first compiled C program!
{{% /task %}}

There are a lot of problems with this implementation: the buffer length is hardcoded and the memory has not been released. A `FileReader` Java class that does everything for you simply cannot be created. As you can see it's a lot more **low-level** work than Java's one-liners like `Files.readAllBytes`! C does not even have the keyword `new`. Ouch.

Key differences between C and a higher level language such as C#:

1. C's syntax footprint is small: no private/protected/class/interface/inheritance/bool/string... No "standard" libraries.
2. C does NOT have exceptions! It works with _interrupts_ and error codes (`return 0`).
3. C does NOT have garbage collection: you manage the memory yourself.
4. C does NOT have a virtual machine (**JVM, CLR**) but gets compiled to native machine code.
5. C code usually is full of pointer variables to manipulate memory directly.
6. C allows for combination-integer-types (`unsigned short int`)
7. C works with headers (.h) and source (.c) files. An executable file requires two steps: compiling and linking. Linking allows for [mixing with assembly](https://www.devdungeon.com/content/how-mix-c-and-assembly).

The following figure represents the Java Virtual Machine you have been using in the INF1 course ([source](https://www.quora.com/What-is-the-Java-virtual-machine-JVM)):

![The JVM](/img/jvm.jpg)

Note that there is **only one** source code and byte code block. Any `.class` file can be executed on any Linux/Windows/MacOS machine, provided you installed the correct JVM on top of the OS, as also pictured. When you compile `.c` C files, they do not translate into byte code but into **OS-specific binaries**! That means you cannot simply share your Windows binaries with a friend that runs Linux on his or her machine. 

### Why should you learn C?

Good question. A few answers:

1. Take a look at the [TIOBE index](https://www.tiobe.com/tiobe-index/) and guess which programming language is the single most used throughout the world. 
2. Since this course is part of an _engineering_ curriculum, it needs to stay close to its engineering roots: **the hardware** (_embedded systems_). Controlling hardware components on a PCB chip can only be done with low level machine instructions, that are coming from a low-level programming language such as C. Of course, writing in Assembly is even more precise, but hurts just a tad bit more. 
3. This is more of an operating systems course than it is a programming course. However, to learn concepts of an OS, you'll need a firm grasp of the basics in C.  

![](/img/tiobe.jpg "The TIOBE Index")

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


The `main()` function returns a number that determines whether or not your program was executed successfully (0), else some kind of error code will be returned. `printf` is a function in the default IO header that we need to include, just like Java's `import`.

The "f" of printf stands for "formatting" as you can see in the example. See [Formatted output](https://www.gnu.org/software/libc/manual/html_node/Formatted-Output.html).

{{% task %}}
Write a program that outputs the following: <br/>
"pi is&nbsp;&nbsp;&nbsp;&nbsp;3.1415"<br/>
Based on the floating-point variable pi with a value of `3.1415`. The output should end with a new line and contain a tab.
{{% /task %}}

### Use functions to structure code

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

You **cannot overload** functions in C, unlike in C++ and Java. That means each function name is unique:

```C
int yay() {
    return 1;
}

int yay() {
    return 0;
}

int main() {
    return yay();   // ??
}
```

Does, depending on the compiler, not compile:

<pre>
test.c:5:5: error: redefinition of 'yay'
int yay() {
    ^
test.c:1:5: note: previous definition is here
int yay() {
    ^
1 error generated.
</pre>

### Primitives and combinational types

The C language provides the four basic arithmetic type specifiers:

1. `char` (1 byte)
2. `int` (4 bytes)
3. `float` (4 bytes)
4. `double` (8 bytes)

Together with the modifiers:

1. `signed` (minus and plus signs supported)
2. `unsigned` (only plus signs, greater range)
3. `short` (/2 bytes)
4. `long` (x2 bytes)

[The table on Wikipedia](https://en.wikipedia.org/wiki/C_data_types) lists the permissible combinations to specify a large set of storage size-specific declarations. `char` is the smallest addressable unit, and `long double` is the biggest. For instance, `unsigned char` gives you a range of 0 to 255, while `signed char` works from -127 to 127. 

{{% notice note %}}
Actual byte sizes are dependent on the target platform - the amount of bytes given above is usually correct for a 64-BIT machine. This can be retrieved using `sizeof(type)`. 
<br/>
<br/>
Try this out for yourself! See the [combinational types demo C file](https://github.com/KULeuven-Diepenbeek/osc-exercises/blob/master/ch1_c/combinational.c) in `osc-exercises/ch1_c/combinational.c`
{{% /notice %}}

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

In C, strings are just concatenations of `char`acters, terminated with `\0`. For instance, `string[] msg = "hey";` looks like this in memory[^dep]:

[^dep]: The backslash (`\`) is depicted as a forward slash (`/`) in the Figure. 

{{<mermaid>}}
graph LR
    H[h]
    E[e]
    Y[y]
    T{/0}
    
    H --> E
    E --> Y
    Y --> T
{{< /mermaid >}}

An elaborated example that illustrates how character sequences work, and how they are terminated with `\0`, can be found at [http://www.cplusplus.com/doc/oldtutorial/ntcs/](http://www.cplusplus.com/doc/oldtutorial/ntcs/).

Handy string utility functions reside in the header file `<string.h>` (copying, concatenating, asking for the length, ...) See [GNU C: String utils](https://www.gnu.org/software/libc/manual/html_node/String-and-Array-Utilities.html).

{{% task %}}
What is the result of `strcmp("hello", "Hello")`? <br/>
And of `strncmp("hello, world", "hello, amazing world!!", 5)`?
{{% /task %}}

Hint: `man strcmp`!

**Online C compilers**:

- https://rextester.com/
- https://godbolt.org/
- https://repl.it/ (requires logging in)


### The C Language - a quick reference

Actually, the ANSI C syntax fits in just _two index cards_ - that's how small it really is. [Download the quick reference cards here](/pdf/c-refcard.pdf). Compared to Java, C# or C++, C is very much falls in the category "easy to learn, hard to master". See the [handbook comparison of C++ and C](https://kuleuven-diepenbeek.github.io/cpp-course/img/teaching/cpp/cppbooks.jpg) and you'll know what we mean. 

