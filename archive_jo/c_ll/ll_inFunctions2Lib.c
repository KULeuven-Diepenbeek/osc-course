#include "ll_inFunctions2Lib.h"

void showLL(T_node **a) {
  int i=0;
  T_node *pointer;

  pointer = *a;
  if (pointer == NULL) {
    printf("the LL is empty\n\n");
  } else {
    while (pointer != NULL) {
      printf("element %d\n  name: %s\n  value: %d\n", i++, pointer->name, pointer->value);
      pointer = pointer-> next;
    }
    printf ("\n");
  }
}

void pushToEndOfLL(T_node **a, char * b, char c) {
  T_node *pointer, *newelement;

  newelement = malloc(sizeof(T_node));
  memcpy(newelement->name, b, sizeof(char)*6);
  newelement->value = c;
  newelement->next = NULL;

  pointer = *a;
  if(pointer != NULL) {
    while (pointer->next != NULL) {
      pointer = pointer->next;
    }
    (*pointer).next = newelement; // equal to "pointer->next = newelement;"
  } else {
    *a = newelement;
  }
}

void popFirstFromLL(T_node **a) {
  T_node *pointer, *pointer2;

  pointer = *a;

  if(pointer != NULL) {
    pointer2 = pointer->next;
    *a = pointer2;
    free(pointer);
  }

}
