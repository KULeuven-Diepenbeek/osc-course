---
title: '4.1: Pointers and arrays'
pre: "<i class='far fa-keyboard'></i> "
weight: 3
---

In the schematic examples below, the following concepts can be explicitly distinguished:

1. The **name** of a variable
2. The **value** of a variable

And the following implicitly:

1. The **type** of a variable
2. The **adres** of a variable

The **type** of a variable determines the amount of memory that is freed up to be able to save the value. The value is either a current value or an address that refers to a different value. Each variable has a unique address. Variables can therefore refer to each other.

{{<mermaid>}}
graph TD;
    A[varname<br/>value]
    B{varname<br/>address}
{{< /mermaid >}}

This example visualizes the instruction `int a = 5`:

{{<mermaid>}}
graph TD;
    A[a<br/>5]
{{< /mermaid >}}

Where the type, `int`, reserves a few bytes depending on the target platform (`sizeof(int)`), on a specific address. We can manipulate the address itself - this is essential when working with arrays.

### "Compound" types

C uses a _pass-by-value_ system to pass variables to functions. This means that the value is copied, and that function cannot make changes to the original value. That is something positive: **separation of concerns**.

When we think of our person example of [chapter 2](/ch2-c), that struct is therefore always copied. That can be very inefficient, depending on the size of the data! To avoid this, we use a "pointer": a reference to the current data. Objects are _passed by-reference_ by default in Java - so in C we have to do something extra for this.

Instead of `is_old(struct Person person)` the signature becomes `is_old(struct Person * person)` (note the added asterik *). We have two options for reading a value here:

1. _"dereferencing"_ the pointer: asking for the real value, behind the reference. Following the arrow where it points towards, so to speak.
2. Ask for members of the pointer using "`.`".

Because in C, the `.` operator takes precedence over `*`, we have to add brackets to combine both: `(*person).age`. It is annoying to constantly have to use brackets, so the creators came up with an alternative, the `->` operator: `person->age`.

{{% notice note %}}
`(*pointervariable).property` equals to `pointervariable->property`.
{{% /notice %}}

In Java properties are accessed using the dot operator `.`.

### Pointer types

A pointer is a "changeable" reference to a variable. Pointers have their own memory address on the stack and can refer to something else at any time: they are not constant. They are recognizable by `*` after variable type.

```C
#include <stdio.h>

int main() {
    int young = 10;
    int old = 80;
    int *age = &young;
    age = &old;

    printf("%d\n", *age);
    printf("%d\n", age);
}
```

{{% task %}}
What will be printed in the above example? The first line should be obvious, but the second one... 
{{% /task %}}

{{<mermaid>}}
graph LR;
    A{*age} -->|after first assignment| B[young<br/>10]
    A -.-> |after second assignment| C[old<br/>80]
{{< /mermaid >}}


Notice the use of the `&` operator, it is the _address-of_ operator to fetch the address of a variable. A pointer points to an address, not to a value (of a variable). 

Look at it this way: I live in streetname, city. When I give you my card, you have a **reference** to my address. I can hand out cards to more people. The card does not represent my house, but points towards it. 
If you wish to do so, you can write a different address on the card, eliminating my previous address. From that point on, your card points to a different address, while other cards I dealt out still point to my original address. 

{{<mermaid>}}
graph LR;
  C{my card} -->|contains directions to| A[my house]
  B[your house]
{{< /mermaid >}}

If I want to get the address of your house, I'd have to use the address-of operator: `&your_house`. If I want to get the house itself (physically impossible...), I'd use the _dereference_ operator on the card: `*card`. This simply **follows the arrow** where card currently points to. 

So, what was the output of `printf("%d\n", age);`? 1389434244! Huh? We are printing the **address** of the pointer, not the actual value (by following where it points to). Remember, to do that, you have to use the dereference `*` operator: `printf("%d", *age);`. The compiler hints at this with the following warning:

> warning: format specifies type 'int' but the argument has type 'int *' [-Wformat]

#### C's By-Value VS Java's By-Ref - redux

Pointers can point to pointers which can point to pointers which can ... Add enough `*` symbols!

```C
int val = 10;
int *ptr = &val;
int **ptr_to_ptr = ptr;
int **ptr_to_ptr = &ptr;
```

{{% task %}}
Why does `int **ptr_to_ptr = ptr;` generate a compiler error?
{{% /task %}}

{{<mermaid>}}
graph LR;
    A{"**ptr_to_ptr"} -->|ref| B{"*ptr"}
    B --> |ref| C[val<br/>10]
{{< /mermaid >}}

Practical use of the double `**` notation would be to relink a pointer to another location. As you know from [chapter two](/ch2-c), variables in C are passed along **by value**: even pointer values. This means a copy of a pointer is created whenever calling a function with a pointer. Chaining the actual value is possible by following the address using the _dereference_ operator. But chaining _the address_ itself is only possible with double pointers:

```C
#include <stdio.h>
#include <stdlib.h>
void increase(int* nr) {
    (*nr)++;
}
void reassign(int** nr, int* dest) {
    *nr = dest;
}
int main() {
    int* nr = malloc(sizeof(int)), *nr2 = malloc(sizeof(int));
    *nr = 10, *nr2 = 5;
    increase(nr);
    printf("%d\n", *nr);    // prints 11
    reassign(&nr, nr2);
    printf("%d\n", *nr);    // prints 5
}
```

#### Pointer instantiation

Where does a new pointer point to that is not yet instantiated?:

```C
int *ptr;
printf("%d", *ptr); // prints -12599900072
```

Whoops. Always assign 'nothing' to a pointer, using `int *ptr = NULL`. Note that depending on the C implementation (such as VC++, clang, GNU C), an uninitialized pointer might contain the value `0`.

`NULL` is a **platform dependent** (!!) macro that in C refers to zero (`0`), usually in the form of a void pointer. A `void *` pointer can refer to any type and is usually used to address low-level memory, as we will see using embedded hardware equipment.

{{% task %}}
What gets printed in the above example if we assign `NULL` to `*ptr`?
{{% /task %}}

The definition of a pointer does not prescribe the exact location of the `*`: `int* age` is the same as` int *age` (notice the placement of the stars). Be careful with things like 'int *age, old_age'! The last variable here is an ordinary int, and not a pointer!

#### Function pointers

Now things are getting interesting. A pointer can also point **to a function**. (Remember the datastructure from [chapter 2](/ch2-c)?). You will need the same signature definition to do that:

```C
#include <stdio.h>

int increase(int nr) {
    return nr + 1;
}

int doublenr(int nr) {
    return nr * 2;
}

int main() {
    int (*op)(int) = &increase;

    printf("increase 5: %d\n", op(5));
    op = &doublenr;
    printf("double 5: %d\n", op(5));
    return 0;
}
```

The definition of the op pointer looks a bit strange, but the signature predicts that we will return an `int` (far left), and that one parameter is needed, also in the form of an` int` (in brackets). If you fail to do so (for instance, by creating a `double doublenr(int nr)` function), weird things happen, but the program does not crash:

<pre>
Wouters-Air:development jefklak$ gcc test.c && ./a.out
test.c:15:8: warning: incompatible pointer types assigning to 'int (*)(int)' from 'double (*)(int)' [-Wincompatible-pointer-types]
    op = &doublenr;
       ^ ~~~~~~~~~
1 warning generated.
increase 5: 6
double 5: 14
</pre>

Function pointers can also be given as a parameter, for example with `void exec (int (* op) (int)) {`. A function can return a function (pointer), for example with `int (* choose_op (int mod)) (int) {`. The function "choose_op" expects 1 int parameter and returns a function pointer that refers to a function with 1 int parameter and return value int. To simplify that mess, `typedef` is usually used:

```C
#include <stdio.h>

typedef int(*func_type)(int);

int increase(int nr) {
    return nr + 1;
}

int doublenr(int nr) {
    return nr * 2;
}

func_type choose_op(int mod) {
    return mod == 0 ? &increase : &doublenr;
}

void exec(int (*op)(int)) {
    printf("exec: %d\n", op(5));
}

int main() {
    exec(choose_op(0));       // print 6
    exec(choose_op(1));       // print 10
    return 0;
}
```

Now you understand how we used the 'callback function' `is_old()` in the Person struct in [chapter 2](/ch2-c).

### Watch out for syntax!

Remember that symbols such as `*` en `&` have different meanings.  

- `int *p;` - * after a type: it's a pointer.
- `p = &i` - & used in an expression: _address-of_ operation
- `*p = i` - * used in an expression: _dereference_ operation

## Ponder on this

1. What is the difference between `char msg[] = "heykes"` and `char *msg = "heykes"`? Clarify your answer with a drawing.
2. Wat is the difference between `int a[10][20]` and `int *b[10]`? Can you also say something about memory usage?
3. In which case would you definitely use pointers in C, and in which case would you not? Explain your choice.
4. What happens when I get the address of a stack variable, like `&x` in section 'changing values around', but the stack got cleared because the method call was finished? 

