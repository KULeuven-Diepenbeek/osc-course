#include <stdio.h>

int main(void) {
  int mijnarray[10];
  int i;

  // void * mijnpointer;
  // mijnpointer = (void * )0x0;

  // printf("%08x", mijnpointer);

  for(i=0;i<10;i++) {
    mijnarray[i] = 10-i;
  }

  for(i=0;i<10;i++) {
    printf ("%d: %d\n", i, mijnarray[i]);
  }

  for(i=0;i<100;i++) {
    printf ("%d: %d\n", i, mijnarray[i]);
  }

}