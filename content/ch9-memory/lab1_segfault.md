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

* Recompile the code above, but verify that you have the ```-0s``` option added. This compiler flag sets the optimisation towards size. What do you learn ?

* Increase the **WRITE_SIZE** to 27. Compile and run again. Any errors ? If so, what type of error could this be ?