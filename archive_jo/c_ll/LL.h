#include <stdio.h>

typedef struct node {
  int value;
  struct node * next;
} T_node;

void showLL(T_node **a);
void addElementToLL(T_node **a, int b);