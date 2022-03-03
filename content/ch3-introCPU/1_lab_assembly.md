---
title: '3.2: Assembly basics'
pre: "<i class='fas fa-vial'></i> "
weight: 2
---

## Assembly basics

### Exercise 1

How would you implement a while loop in Assembly using BEQi and JMPi? 

You don't need to write out the full RAM contents nor variable addresses, just the instruction addresses and Assembly instructions (as in exercise 4 below).

``` C
int accumulator = 0;
int n = 10;
while( n != 0 ) {
    accumulator += 10;
    n--;
}
int a = accumulator + 5;
```

### Exercise 2

How would you implement a for loop in Assembly using BEQi and JMPi? How is this different from the while in Exercise 1 above?

You don't need to write out the full RAM contents nor variable addresses, just the instruction addresses and Assembly instructions (as in exercise 4 below).

``` C
int accumulator = 0;
for( int n = 10; n != 0; n-- ) {
    accumulator += 10;
}
int a = accumulator + 5;
```

### Exercise 3 

Show what the full RAM contents might look like after executing the following pseudo-C program. Show both variables (A, B, C, ...) and encoded instructions.
You can choose yourself at which addresses you place the variables and where you start placing the instructions. 

Use the following opcodes if necessary: MUL = 6, MULd = 7, MULi = 8, DIV = 9, DIVd = 10, DIVi = 11,
BEQ = 12, BEQi = 13, BNE = 14, BNEi = 15, BLT = 16, BLTi = 17, BLE = 18, BLEi = 19,
JMP = 20, JMPi = 21

``` C
A = 5
B = 10
D = 20
if ( A > 15 ) {
    B = D * 10
}
else {
    A += 15
    B = D * 10
}
C = 5 + (B / A);
```

_Tip: a single line of C code might need multiple lines of Assembly code!_

### Exercise 4

Below, you can see a (psuedo) C program on the left.
It has been translated to the Assembly on the right, but the programmer has made some major errors!

Can you find an fix the errors in the Assembly?

<div class="multicol">
<div>

``` C
if ( A == 15 ) {
    B = 10;
    if ( C < X ) {
        Y = 20;
    }
    else {
        Z = 30;
    }
}
C = X;
```

</div>
<div>

```
0x08: BEQi A 15 0x20
0x0C: ADDd B B 10
0x10: BLE X C 0x18
0x14: ADDi Y 20 Y
0x18: JMP 0x20

0x1C: ADDi Z 30 Z


0x20: ADDi X C
```

</div>
</div>

### Exercise 5

Did you know that `X++` and `++X` have subtly different meanings in most programming languages? 

Specifically:

<div class="multicol">
<div>

``` C
int A = 1;
int B = ++A;
// A is now 2
// B is now 2
D = B + 1;
// D is now 3
```

</div>
<div>

``` C
int A = 1;
int B = A++;
// A is now 2
// B is now 1 !!!!!!! (not 2 !!!)
D = B + 1;
// D is now 2 !!!!!!! (not 3 !!!)
```

</div>
</div>

As you can see, if `X++` is used in combination with an assignment (`Y = X`), the assignment will happen first, and only then does the increment (`++`) happen.

The opposite is true for `++X`: there the increment happens first, and then the assignment is done. 

Write both options in Assembly (using ADDi and ADDd instructions) showing clearly how they're different. 

_Note: this shows that a single statement in C can often compile to 2 or even more assembly instructions, and the implications are often subtle!_

_Note: when used in while/for loops (see Exercise 1 and 2), it typically doesn't matter if you do --X or X--, they both end up the same in those cases_

