---
title: '2.2: String Manipulation'
pre: "<i class='fas fa-vial'></i> "
weight: 2
---

## We are at War!

We're at **war**! The orcs are attacking and are looking very hungry! Look at them! 

{{% figure src="/img/labs/orcs.png" title="Orcs attacking! source: G.I."%}}

### 1. String manipulation

However, instead of simply killing you, these not so friendly looking beasts target _vowels_ instead of _bowels_. So when speaking to, they munch and munch, stripping your carefully chosen words of all vowels. How rude. Implement a function called `char* munch(char* sentence)` that obscures all vowels with an 'X', and then prints the results. You will also need a `int main()` function. 

Assume a maximum character length of 100 for the input sentence.

Tips:

1. Re-read [chapter 2](/ch2-c/).
2. How do you start writing a program in C? Create one file, create a main function, print something and compile/run to test if it works. Then expand. 
3. Will you be using `scanf()` or `fgets()` for user input? What is the difference? Look up how to use either functions. 
4. You can safely ignore the `*`. A char array gets converted to a pointer if returned or given as an argument. Remember, in Java, the function signature would simply be `char[] munch(char[] sentence)`
5. Go through the [GNU Coding standards](https://www.gnu.org/prep/standards/html_node/Writing-C.html). Methods in C are _snake-cased_: `my_nice_method` instead of Java's _camelcasing_ `myNiceMethod`.

<pre>
INPUT: 'hello friendly green guys'
OUTPUT: 'hXllX frXXndly grXXn gXys'
</pre>

Start from this blueprint:

```C
#include <stdio.h>
#include <stdlib.h>

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

The correct use of `malloc()` will be explained in the coming labs.
