---
title: '1.3: Creating order: Structures'
pre: "<i class='fas fa-book'></i> "
weight: 2
---

### Structs

The only way to structure data in C is using the `struct` keyword:

```c
struct Person {
    int age;
    int gender;     // no bool, remember?
    char name[100]; // do not forget to add a size
}
```

We can use this structure to assign values like this:

```c
struct Person jaak;    // do not forget "struct"
// jaak.name = "Jaak Trekhaak"; - this is too easy - won't work
strcpy(jaak.name, "Jaak Trekhaak"); // include <string.h> for this
jaak.age = 80;
jaak.gender = 1;
```

Another way of assigning values is defining the values inline using the `{}`brackets:

```c
struct Person jaak = {
    "Jaak Trekhaak",    // need to be in order of property definition
    80,
    1
};
```

The next question is, can we also define functions in a `struct`? Yes and no. A function pointer makes this possible, but it is not the same such as a member variable of a class in Java. C function pointers, however, can be very usefully used as _callback methods_:

```c
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
    jaak.is_old = &is_old;

    printf("is jaak old? %d\n", jaak.is_old(jaak));  
}
```

It looks a bit weird because there is no such thing as a magical variable named `this` - that's one argument you have to provide yourself. You can emulate functions as members of a data structure, but as you can see it's going to cost you. The function pointer, or callback method, will be further explained in [chapter 2](/theory/c/chap2).

{{<task>}}
Compile and execute the above code. what happens when you comment out `jaak.is_old = &is_old;`?<br/>
Implement another function with signature `int f(struct Person p)` that calls people old when they are called "Jaak". Look at the previous example on how to expand the struct to add a name property.
{{</task>}}

#### Extra definitions

Creating a person looks awkward: `struct Person jaak;` - why can't we simply use `Person jaak;`? That is possible if you **define** your own types using the keyword `typedef`. It's also useful to emulate your own `string` implementation:

```c
typedef struct Person Person;
typedef char* string;
```

Magic numbers are usually defined on top, in header files, using `#define`. With some tricks we can emulate booleans in C:

```c
#define TRUE 1
#define FALSE 0

typedef unsigned short int bool;

bool male = TRUE;
```

These `#define` statements are **preprocessor flags**. These can be as simple as this example or as complex as switching on different CPU architectures and executing another set of rules depending on the outcome. Macros are expanded just before expanding, see the "compiling" section below. Intricate examples are visible at [Wikipedia](https://en.wikipedia.org/wiki/C_preprocessor).

Typical C code that you may encounter due to lack of a bool: `if (result) {...}` where result is an `int`. This is in **no case** the same as [JavaScripts Truthy / Falsey](https://j11y.io/javascript/truthy-falsey/) construction! The number `0` is false. `EOF`,` NULL` or `\ 0` all evaluate to a number to use this.

#### C's By-Value VS Java's By-Ref

In C, everything you pass to functions is passed _by value_, meaning a **copy of the value** is created to pass to the called function. This is _very important_ to grap because mistakes are easily made. For instance, by passing the Person struct, we copy it. Any changes made to the struct in the function are done ON THAT COPY:

```c
void happy_birthday(Person person) {
    person.age++;
}
int main() {
    Person jaak;
    jaak.age = 13;
    happy_birthday(jaak);
    printf("%d\n", jaak.age);   // HUH? Still 13?
}
```

The copy of jaak gets to celebrate, but jaak himself stays 13.

{{<mermaid>}}
graph LR;
    main{main}
    happy{happy_birthday}
    jaak[Person jaak]
    copy[copy of jaak]

    jaak -.->|create copy| copy
    main -->|push to main stack| jaak
    happy -->|push to local fn stack| copy
{{< /mermaid >}}

To fix this, we need the use of **pointers**, as explained in [chapter two](/theory/c/chap2). In Java, every object is passed _by reference_, meaning it points to the same value and changes will be persistent. As expected, In Java (and in pretty much any other programming langauge) this is not the case for primitives:

```java
public static void increase(int i) {
    i++;
}
public static void main(String[] args) {
    int i = 5;
    increase(i);
    System.out.println("i is " + i);    // still 5
}
```

## Use of header Files

The `#include` statements ensure the correct inclusion of functions in your program. Large programs consist of multiple C (source) and H (header) files that are glued together with compiling and linking. A header file contains function **definitions**, the **declarations** are in the source files:

```c
// person.h

struct Person {
    int age;
}
int is_old(struct Person p);
```

With the following source file:

```c
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
    B --> E[definition is_old]
    A{person.h} -->|source| C[facebook.c]
    C --> F[use struct]
    A{person.h} -->|source| D[twitter.c]
    D --> G[use struct]
{{< /mermaid >}}

If you create a separate header file and include them into the source files, there is no need to compile or link it separately. That is, `gcc code.c` still suffices. Only when you split up source code into separate **source files**, multiple output files will need to be compiled - and linked together (with one `main()` function present somewhere).