#include <stdio.h>

void temp(int a) {
  printf ("hello from temp (%d)\n", a);
}

int main(void) {
  int a = 0, i;

  for(i=0;i<10;i++) {
    printf ("hello from main (%d)\n",i);
    temp(i);
  }

  return 0;
}