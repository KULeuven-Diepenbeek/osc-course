---
title: '3.4: The Stack'
pre: "<i class='fas fa-vial'></i> "
weight: 4
---


## Exercise 1

Write the (psuedo)Assembly code (using PUSH/POP) for the following C code (note: you can re-use a lot of the example code in the chapter to start, but you'll need to add/change a lot too!).

Since we're now calling additional functions, also make sure you store the return addresses on the stack correctly (using 0x07 as temporary return address storage).

You can use 0x60, 0x61 and 0x62 as addresses for the input parameters (M, N, R, S, and T), and 0x80 to store any return values. Alternatively/additionally, you can also pass around values using the stack. Both approaches will have pros and cons and situations where you have to work around them. 

_To keep things simple, you don't have to store local variables (like C, D, Q, etc.) on the stack and can pretend they just reside at an appropriate address, like in the examples in the chapter._


``` C
void fX() {
    int A = 1;
    int B = 2;
    int C = fY(A, B); 
    int D = C + A;
}

int fY(int M, int N) {
    int Q = M + N;
    int R = fZ(Q, M, N);
    R = R + M;
    return R;
}

int fZ(int R, int S, int T) {
    int U = R * S * T;
    return U;
}

```

## Exercise 2

A recursive function is **a function that calls itself**. This might seem weird, but it is actually quite useful in many situations, as it makes code easier to understand. You will learn more about practical use cases for recursive functions in later classes. 

For now, consider the following simple recursive function that counts to 10 and the function `f1` that calls it:

``` C
void f1() {
    int Y = countToTenRecursive(0);
    int Z = Y + 10; // should be 20!
}

void countToTenRecursive(int currentNumber) {
    if ( currentNumber >= 10 ) {
        return currentNumber;
    }

    int nextNumber = currentNumber + 1;
    return countToTenRecursive( nextNumber );
}

```

Your goal is to write Assembly (using the stack of course!) that properly implements this function.
You can assume that a function retrieves its first parameter (in this case `currentNumber`) from the address 0x60 and stores its return parameter in 0x80. 

_Before you start, consider what exactly it means to return a function call as we do here at the end of `countToTenRecursive`_

Take care to correctly store the return addresses (and potentially also the return values and function parameters) on the stack so that, even 10 calls deep, things still work as expected!

## Exercise 3

There are many types of Assembly. One of the most recent ones is called "WebAssembly", a somewhat high-level Assembly language (if that's not a "contradictio in terminis", I don't know what is) that can be used as an alternative for JavaScript.

WebAssembly is special in that it works purely by means of a "stack machine". Put differently: all of its instructions/operations work by pop'ing and push'ing things from/to the stack. If it's not on the stack, you can't perform calculations with it. 

For example: while `C = 10 + 5` would look like this in our pseudo-assembly: `ADDd 10 5 C`, in (conceptual) WebAssembly it would instead be this:

```
PUSHi 10  // put value 10 on the stack
PUSHi 5   // put value 5 on the stack
ADDd      // pops the top two values from the stack, add them together, then push the result back onto the stack
POP C     // store the top value of the stack in address C
```

Using this approach, write (conceptual) WebAssembly code for the following functionality:

- Given a value on the stack (put there by some previous operation), subtract 20 from it
- Given a value on the stack (put there by some previous operation), square it (e.g., if the value is 5, we want to do 5*5)
- `void f1(int A) { B = 25 + A; C = B + 10; return C; }`

Answer the following questions:
- Do we still need 3 variants of our mathematical operations (for example ADD, ADDd and ADDi) or can we do with less? Why?
- "Using the stack in this way is better than the "normal"/pseudo Assembly we've seen because it reduces the amount of temporary variables we need." Is this statement true or false? Why?

## Exercise 4

In most programming languages, a function can only have a single return value. If you want to return multiple values, you have to wrap them in an object/struct or use pointer input parameters (see later).

However, there is no real technical reason for this... a stack can perfectly be used to support multiple return values for a single function.

Can you write a simple Assembly (pseudo)code sample that shows this concept? 

What this might look like in C if C allowed multiple return values:

``` C
int A, B = f1();
int C = A + B;

int,int f1(){
    M = 20;
    N = 30;
    return M, N;
}
```