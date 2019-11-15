#include <stdio.h>
#include <unistd.h>

#define DURATION_IN_MINUTES .5

int main(void) {
  int i;

  printf("hello world !\n");
  printf("FYI: my PID is 0x%ld\n", (long)getpid());
  printf("validate I'm not lying using ps ... \n");

  for(i=0;i<(DURATION_IN_MINUTES*60);i++) {
    sleep(1);
  }

  return 0;
}