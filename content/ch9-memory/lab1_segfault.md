---
title: '9.2: Deliberate Segfaulting'
pre: "<i class='fas fa-vial'></i> "
weight: 2
---

{{<figure src="/img/compiler_complaint.png" title="source: xkcd.com">}}

## Segfault this

For each of the programs below:

* Guess first if they will give a segmentation fault and where exactly and **why**
* Compile and execute them
* Were your guesses in the first step correct or not? Why (not)?

<!-- try to force end of the list -->

```C
#include <stdio.h>

int main(void) {

	int* i = NULL;
	*(i) = 666;

	return 0;
}
```

```C
#include <stdio.h>

int main(void) {

	int i = 666;
	*(&i - 10000) = 777;

	return 0;
}
```

```C
#include <stdio.h>

int main(void) {

	int i = 666;
	*(&i + 10000) = 777;

	return 0;
}
```

* Try and change the number "10000" to higher and lower numbers in the previous two code samples to help make sense of what's happening.

<!-- try to force end of the list -->

```C
#include <stdio.h>
#include <stdlib.h>

int main(void) {

	int *i = (int *) malloc(26 * sizeof(int));
	
	*i = 20;
	
	*(i + 27) = 30;
	
	free(i);
	
	*i = 40;

	return 0;
}
```

* Try and change the number "100" to "26" and the number "101" to "27" and run the program again. Do you get the same results? 

## A to the Z

As we've seen in the previous exercises, segmentation faults don't always happen when we expect them to.
Let's explore this a bit deeper here. 

* Again, first guess if the program below will give a segmentation fault or not (and why!)
* Compile and run the program and verify your guess

```C
#include <stdio.h>

#define WRITE_SIZE 26
#define READ_SIZE 27

int main(void) {
	int i;
	unsigned char alphabet[26];

	for(i=0;i<WRITE_SIZE;i++) {
		alphabet[i] = 65 + i;
	}

	for(i=0;i<READ_SIZE;i++) {
		printf("%2d -> %c (%02x)\n", i, alphabet[i], alphabet[i]);
	}

	return 0;
}
```

* Now, recompile the code above, but verify that you have the ```-0s``` option added for gcc. This compiler flag sets the optimisation towards size, but also adds a few more interesting things. Does that make a difference? 

* Now increase the **WRITE_SIZE** to 27. Compile and run again, with and without the ```-0s``` option. Any errors? If so, what type of error could this be?

* Compare this to the last code sample of the first exercise above. What is different about which memory we are trying to access here? 

* Do some research online until you can explain what a "stack canary" is and why it's useful. 
