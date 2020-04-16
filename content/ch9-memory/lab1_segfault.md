---
title: '9.2: Deliberate Segfaulting'
pre: "<i class='fas fa-vial'></i> "
weight: 2
---

{{<figure src="https://imgs.xkcd.com/comics/compiler_complaint.png" title="source: xkcd.com">}}


## <s>X</s> A to the Z

* Run the program below and verify that it runs without errors
```C
#include <stdio.h>

#define ACTUAL_SIZE 26
#define READ_SIZE 27

int main(void) {
	unsigned char alphabet[ACTUAL_SIZE];

	for(int i=0;i<ACTUAL_SIZE;i++) {
		alphabet[i] = 97 + i;
}

	for(int i=0;i<READ_SIZE;i++) {
		printf("%2d -> %c (%02x)\n", i, alphabet[i], alphabet[i]);
	}

	return 0;
}
```

* Recompile the code above, but verify that you have the ```-0s``` option added. This compiler flags sets the optimisation towards size. What do you learn ?

* Increase the **READ_SIZE** to 100. Compile and run again. Any errors ?

*