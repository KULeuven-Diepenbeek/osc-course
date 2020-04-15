---
title: '9.2: Deliberate Segfaulting'
pre: "<i class='fas fa-vial'></i> "
weight: 2
---

{{<figure src="https://m.media-amazon.com/images/I/71rZ7W8knkL._AC_UX679_.jpg" title="source: amazon.com">}}

* Run the program below and verify that it runs without errors
```C
#include <stdio.h>

int main(void) {
	unsigned char alphabet[26];

	for(int i=0;i<26;i++) {
		alphabet[i] = 97 + i;
	}

	for(int i=0;i<27;i++) {
		printf("%2d -> %c\n", i, alphabet[i]);
	}

	return 0;
}
```


## Let's compare !

We have discussed a number of algorithms the scheduler can use to do it's job. Let's compare them. We assume the following tasks:

* T1: arrives @ 0s, takes 10s, and has priority low
* T2: arrives @ 1s, takes 2s, and has priority high
* T3: arrives @ 4s, takes 5s, and has priority medium
* T4: arrives @ 7s, takes 1s, and has priority high

Compare Threshold, AJWT, and AJCT of the 4 algorithms we've seen up until: 

0. cooperative (non preemptive) FCFS, 
0. cooperative (non preemptive) SJF, 
0. preemptive priority based, and 
0. preemptive round robin, 

