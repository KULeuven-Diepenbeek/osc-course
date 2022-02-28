---
title: '3.4: The Stack'
pre: "<i class='fas fa-vial'></i> "
weight: 4
---


## Exercise 1

Write the Assembly code (using PUSH/POP) for the following C code (note: you can re-use a lot of the example code in the chapter to start, but you'll need to add/change a lot too!).

Since we're now calling additional functions, also make sure you store the return addresses on the stack correctly (using 0x07 as temporary return address storage).


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
    int X = 0;
    int Y = countToTen(X);
    int Z = Y + 10; // should be 20!
}

void countToTenRecursive(int currentNumber) {
    if ( currentNumber == 10 ) {
        return currentNumber;
    }

    int nextNumber = currentNumber + 1;
    return countToTenRecursive( nextNumber );
}

```

Your goal is to write Assembly (using the stack of course!) that properly implements this function.

_Before you start, consider what exactly it means to return a function call as we do here at the end of `countToTenRecursive`_

_Take care to correctly store the return addresses, return values and function parameters on the stack so that, even 10 calls deep, things still work as expected!_

## Exercise 3

TODO: stack machine: operations do POP and PUSH automatically.

Implement a + 20 function, an ADD function, a square function (A * A), as well as A = A + INPUT; B = A + 10; return B; using the stack machine