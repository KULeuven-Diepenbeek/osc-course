#include <stdio.h>
#include <stdlib.h> /* to use malloc */
#include <string.h> /* to use memcpy */

typedef struct node {
  char name[6];
  char value;
  struct node * next;
} T_node;


void showLL(T_node **a);

void pushToEndOfLL(T_node **a, char * b, char c);

void popFirstFromLL(T_node **a);
