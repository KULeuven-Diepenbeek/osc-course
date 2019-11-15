#include <stdio.h>
#include <unistd.h>

#define DURATION_IN_MINUTES 2

int main(void) {
  int i;

  for(i=0;i<(DURATION_IN_MINUTES*60);i++) {
    printf("hello world !\n");
    sleep(1);
  }

  return 0;
}
