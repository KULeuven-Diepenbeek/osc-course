#include <stdio.h>

typedef struct node {
  char name[6];
  char value;
  struct node * next;
} T_node;

int main(void) {

  printf("%d\n", sizeof(T_node));

  return 0;
}
