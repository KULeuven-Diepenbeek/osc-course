---
title: 'Lab 1: Introduction to C'
---

## We are at War!

We're at **war**! The orcs are attacking and are looking very hungry! Look at them! ([img src](https://www.google.be/url?sa=i&rct=j&q=&esrc=s&source=images&cd=&cad=rja&uact=8&ved=2ahUKEwjmyPWi2N7jAhUIxoUKHWLZCmgQjhx6BAgBEAM&url=https%3A%2F%2Fwww.artstation.com%2Fartwork%2Fe5ZDb&psig=AOvVaw2XqhvpDcX5bqiky-tRoQaN&ust=1564646412604432))

![Orcs attacking](/img/labs/orcs.png)

### 1. String manipulation 

However, instead of simply killing you, these not so friendly looking beasts target _vowels_ instead of _bowels_. So when speaking to, they munch and munch, stripping your carefully chosen words of all vowels. How rude. Implement a function called `char* munch(char* sentence)` that obscures all vowels with an 'X', and then prints the results. You will also need a `int main()` function. 

Assume a maximum character length of 100 for the input sentence.

Tips:

1. Re-read [chapter 1](/theory/c/chap1).
2. How do you start writing a program in C? Create one file, create a main function, print something and compile/run to test if it works. Then expand. 
3. Will you be using `scanf` or `gets` for user input? What is the difference? 
4. You can safely ignore the `*`. A char array gets converted to a pointer if returned or given as an argument. Remember, in Java, the function signature would simply be `char[] munch(char[] sentence)`
5. Go through the [GNU Coding standards](https://www.gnu.org/prep/standards/html_node/Writing-C.html). Methods in C are _snake-cased_: `my_nice_method` instead of Java's _camelcasing_ `myNiceMethod`.

<pre>
INPUT: 'hello friendly green guys'
OUTPUT: 'hXllX frXXndly grXXn gXys'
</pre>

Start from this blueprint:

```C
#include <stdio.h>

char* munch(char* sentence) {
    char* response = malloc(sizeof(char) * 100);
    // TODO eat those vowels!

    return response;
}

int main() {
    char sentence[100];
    // TODO read input
    printf("INPUT: %s\n", sentence);
    printf("OUTPUT: %s\n", munch(sentence));
}
```

The correct use of `malloc()` will be explained in the second lab.

### 2. Modelling the orcs

Let us try to model these filthy beasts. Ask the user for a number. That number is the amount of orcs in the army. Create as many `struct` instances with random property values and print these on the screen. An orc has the following properties (both simple numbers, between 1 and 10, use [rand()](https://www.tutorialspoint.com/c_standard_library/c_function_rand) from `stdlib`):

* `attack`
* `life`

<pre>
INPUT: 3
OUTPUT: orc 1: attack 3, life 5. orc 2: attack 5, life 6. orc 3: attack 1, life 1.
</pre>

Tips:

1. Do not forget to generate a new seed for the random value, see the `rand()` docs.
2. Creating a separate function `generate_orcs()` will keep your `main()` function short and clean. The function will return a list of orcs, the "army", so to speak. Remember that returning an array is of type `Orc*`.

### 3. Orcs eating each other??

Vowels did not seem to fully satisfy them, now they are turning on each other!? All the better for us. Expand the program such that the first orc fights the next one. (life minus attack). Create a function `Orc fight(Orc attacker, Orc defender)`. Is the defender still alive after the attack? Then he is victorious (and will be returned). Print the last man stending. Input stays the same. 

<pre>
INPUT: 3
OUTPUT:
  orc 1: attack 3, life 5. orc 2: attack 5, life 6. orc 3: attack 1, life 1.
  orc 1 VS 2: 2 wins (6 - 3 = 3 life left)
  orc 2 VS 3: 2 wins (1 - 5 = dead)
  orc 2 is victorious!
</pre>

Tips:

1. You will need to loop through all orcs and take two elements out of the array to pit them against each other. Reassign `Orc winner = army[0]` with the result of the `fight()` function, within the loop.

### 4. Building with Makefiles

It is time to split up our code into different parts:

{{<mermaid>}}
graph TD
    E{Executable}
    A[main.c]
    AA>main.o]
    B[orcs.c]
    BB>orcs.o]
    D[orcs.h]
    
    E --> AA
    E --> BB

    AA --> A
    AA --> D

    BB --> B
    BB --> D
{{< /mermaid >}}

Create four different files:

1. orcs.h - this is where your struct definition resides.
2. orcs.c - this is where your methods related to orcs reside. Include the orc header file.
3. main.c - this is where your main method resides. Include the orc header file.
4. Makefile - builds everything. Create a `compile`, `link`, and `clean` target.

Compile both C files with separate `gcc -c` commands, merging them together with a third command, as seen in the theory. 
