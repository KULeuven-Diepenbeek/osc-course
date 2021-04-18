
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

	while(1) {
		sleep(1);
		printf("allocating a pretty large block! hahahaha\n");
		malloc(1024 * 10 * 10);
	}

	return 0;
}