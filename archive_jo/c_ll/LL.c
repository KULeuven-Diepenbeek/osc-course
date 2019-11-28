#include <stdio.h>
#include <stdlib.h> /* to use malloc */

#include "LL.h"

void showLL(T_node **a) {
  T_node * pointer;
  pointer = *a;

  if (pointer == NULL) {
    printf("the LL is empty\n");
  } else {
    printf ("values: ");
    while (pointer != NULL) {
      printf("%d, ",pointer->value);
      pointer = pointer-> next;
    }
    printf ("\n");
  }
}

void addElementToLL(T_node **a, int b) {
  T_node *pointer;
  T_node *newelement;

  newelement = malloc(sizeof(T_node));
  newelement->value = b;
  newelement->next = NULL;

  pointer = *a;
  if(pointer != NULL) {
    while (pointer->next != NULL) {
      pointer = pointer-> next;
    }
    (*pointer).next = newelement; // equal to "pointer->next = newelement;"
  } else {
    *a = newelement;
  }

  printf("%d is added\n", b);
}
