---
title: '8.3: Different Scopes in C'
pre: "<i class='fas fa-book'></i> "
weight: 3
---

## Scoping issues

Now that you have some basic knowledge on the stack and the heap, it is time to take a better look at the different scopes present in the C programming language. These concepts are very important because they in part determine whether variables live (or not) - and whether anything is pushed to the local stack (or not). Let's start with a basic example:

```c
#include <stdio.h>

void* whats_my_age() {
    int age = 30; // I'm being generous here!
}

int main() {
    int* my_age = (int*) whats_my_age();
    printf("%d\n", *my_age);
}
```

{{% task %}}
What is the output of the above program? I'm sure you know the answer, but... why?
{{% /task %}}

If you forget how `void*` works, please re-read [chapter 4: pointers and arrays](/ch4-pointers).

You can accidentally get the handle of another pointer that way. Inspect the following code carefully:

```c
#include <stdio.h>
#include <stdlib.h>

int* p;

void* whats_my_age() {
    p = malloc(sizeof(int));
    *p = 5;

    int age = 30; // I'm being generous here!
}

int main() {
    printf("hey");
    int* my_age = (int*) whats_my_age();

    printf("ptr p is p(%p), x(%x) \n", p, p);
    printf("ptr my_age is p(%p), x(%x) \n", my_age, my_age);
}
```

Formatting `%p` (pointer) or `%x` (hex values) result in the same, with or without the `0x` prepend, printing the raw pointer address. Are these the same or different? How about printing the values of both variables by dereferencing them and using `%d`? Are those the same or different? Why? 

Try these out locally or on https://godbolt.org/ using different C compilers (Clang, GCC, MSVC). Sometimes these behave differently!

#### Local variables

The _local_ variabel, `age`, exists as soon as `whats_my_age` is pushed to **the stack**. That automatically includes all locally defined variables. When the method is done, after the `}` sign, things are popped from the stack to make room for future methods and their local variables. This means `whats_my_age` and `age` disappear. Forever. 

If we were to try and change the `age` variable from inside the `main()` method (another method, so the variable is not local anymore) by adding `age = 5;` in the main method, we would get a compile error:

<pre>
scoping.c:9:5: error: use of undeclared identifier 'age'
    age = 5;
    ^
1 warning and 1 error generated.    
</pre>

Nothing shocking there. Identifiers are **undeclared** when they are not present in **the program stack**. 

As a side note referenced from [here](https://gribblelab.org/CBootCamp/7_Memory_Stack_vs_Heap.html), there is a way to tell C to keep a stack variable around, even after its creator function exits, and that is to use the `static` keyword when declaring the variable. A variable declared with the static keyword thus becomes something like a global variable, but one that is only visible inside the function that created it. 

For instance:

```c
static int i;
int j;
int main() {
    // do something!
    return 0;
}
```

We say that `i` is **not** visible outside the module, while `j` **is** visible. Again: adding `static` _reduces_ visibility, it does not enhance it! 

- `i` has what is called _internal linkage_. You cannot use the name `i` again for variables or functions in any other source files.
- `j` has what is called _external linkage_. You can still use `j` from other compilesets using the keyword `extern`, like this: `extern int j;`

The keyword `extern` is used to declare a C variable without defining it. You're telling the compiler "all right, I've got this variable x, but it's defined somewhere else, ok?". Thus, it extends the visibility of the variable (or function). It's a strange construction, one that you probably won't need except under very specific circumstances.

#### Global variables

Once we change the above program by moving `age` outside of the method scope, into the **global scope**, we get something like this:

```c
#include <stdio.h>

int age;
void whats_my_age() {
    age = 30;
}

int main() {
    whats_my_age();
    printf("%d\n", age);
}
```

{{% task %}}
Compile the above program. It correctly prints the age. What is the biggest disadvantage of having a global variable?
{{% /task %}}

Can you figure out where global variables resize in the memory of a program? Take another good look at the schematic in [8.1: program memory](/ch8-stack/stackvsheap). It lives **outside of** the stack, _and also_ outside of the heap, in a separate block called "data". Note that we are not employing any kind of pointer system. Thus, we are not calling upon the heap to transfer data from one method to the other. 

**When should I use global variables?** The answer is _never_, if possible. In practice, in an iterative programming language such as C, that is very difficult to achieve. In essence, function and `struct` declarations are all part of the global scope. Methods can be accessed from any other method (provided you used _forward declarations_), because the method name itself is declared globally, instead of locally. 

Consider the following example in Javascript:

```javascript
function someMethod() {
    int age = 30;

    function someMethodInAMethod() {
        age = 5; // will work: the variable is part of this (closed) scope
    }

    someMethodInAMethod();
}

function otherMethod() {
    age = 5; // will not work: age is accessible in someMethod only

    otherMethod(); // will work and cause an infinite loop
    someMethodInAMethod(); // will not work: same reason as age 
}
```

Calling functions within functions is only possible in C in the form of function pointers leveraging the power of `void*`, but there is no change in the functionality of the scopes. In C, everything in **top level** is _global scope_. Top level is declared as the lowermost level, the body of your source file where all delcarations are put. `main()` is globally scoped at top level. In the above JS example, so is `someMethod`, but not `someMethodInAMethod`: that method is not part of the global scope. 

In practice, most C programs are constructed as a sequence of method calls, all residing in the global scope. You should try to avoid using global _variables_ as any method can change the value of that variable, causing all kinds of wreckage. If you need to pass something, use `return`. If you need to pass multiple things, use a `struct`, or refactor it!
