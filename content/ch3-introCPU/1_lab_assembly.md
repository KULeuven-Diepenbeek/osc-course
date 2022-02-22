---
title: '3.2: Assembly basics'
pre: "<i class='fas fa-vial'></i> "
weight: 2
---

## Assembly basics

### Exercise 1 

TODO: Show what the RAM looks like for 

With initial values: A = 5, B = 10, D = 20
Opcodes: MUL = 6, MULd = 7, MULi = 8, DIV = 9, DIVd = 10, DIVi = 11
BEQ = 12, BEQi = 13, BNE = 14, BNEi = 15, BLT = 16, BLTi = 17, BLE = 18, BLEi = 19
JMP = 20, JMPi = 21

```
C = A + B
A = A + D
E = A - B
F = E * E
```

### Exercise 2

TODO: Optimize this by eliminating as many variables as possible (using the -d and -c variants)

### Exercise 3

TODO: This is the C code, this is the assembly, but we've made a few mistakes... find them and fix them!

### Exercise 4

Did you know that `X++` and `++X` have subtly different meanings in most programming languages? 

Specifically:

<div class="multicol">
<div>

``` C
int A = 1;
int B = ++A;
// A is now 2
// B is now 2
```D = C - 10;
```

</div>
<div>

``` C
int A = 1;
int B = A++;
// A is now 2
// B is now 1 !!!!!!! (not 2 !!!)
```

</div>
</div>

As you can see, if `X++` is used in combination with an assignment (`Y = X`), the assignment will happen first, and only then does the increment (`++`) happen.

The opposite is true for `++X`: there the increment happens first, and then the assignment is done. 

Write both options in Assembly (using ADDi and ADDd instructions) showing clearly how they're different. 

_Note: this shows that a single statement in C can often compile to 2 or even more assembly instructions, and the implications are often subtle!_

### Exercise 5

How would you implement a while loop in ASSEMBLY using BEQi and JMPi?

```
int accumulator = 0;
int n = 10;
while( n != 0 ) {
    accumulator += 10;
    --n;
}
int a = accumulator + 5;
```

### Exercise 6

How would you implement a For loop? 

```
int accumulator = 0;
for( int i = 10; i > 0; ++i ) {
    accumulator += 10;
}
int a = accumulator + 5;
```