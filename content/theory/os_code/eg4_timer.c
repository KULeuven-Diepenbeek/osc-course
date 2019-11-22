#include <stdio.h>
#include <unistd.h>

#define DURATION_IN_MINUTES 10

int main(void) {
  int i = DURATION_IN_MINUTES * 60;

  for(;i>=0;i--) {
    printf("TIMER: 00:%02d:%02d\n", (int)((i-i%60)/60), i%60);
    sleep(1);
  }

  return 0;
}