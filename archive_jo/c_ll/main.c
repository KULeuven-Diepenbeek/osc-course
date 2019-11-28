#include <stdio.h>
#include <stdlib.h> /* to use malloc */
#include <string.h> /* to use memcpy */

typedef struct node {
  char name[6];
  char value;
  struct node * next;
} T_node;

int main(void) {
  char values = 10;
  T_node *head, *pointer, *newelement;
  int i;

  head = NULL;

  // show LL
  pointer = head;
  if (pointer == NULL) {
    printf("the LL is empty\n\n");
  } else {
    while (pointer != NULL) {
      printf("element %d\n  name: %s\n  value: %d\n", i++, pointer->name, pointer->value);
      pointer = pointer-> next;
    }
    printf ("\n");
  }

  // PUSH FIRST element to end of LL
  newelement = malloc(sizeof(T_node));
  memcpy(newelement->name, "hello", sizeof(char)*6);
  newelement->value = values++;
  newelement->next = NULL;
  head = newelement;

  // show LL
  i=0;
  pointer = head;
  if (pointer == NULL) {
    printf("the LL is empty\n");
  } else {
    while (pointer != NULL) {
      printf("element %d\n  name: %s\n  value: %d\n", i++, pointer->name, pointer->value);
      pointer = pointer-> next;
    }
    printf ("\n");
  }

  // PUSH NEXT element to end of LL
  newelement = malloc(sizeof(T_node));
  memcpy(newelement->name, "world", sizeof(char)*6);
  newelement->value = values++;
  newelement->next = NULL;
  pointer = head;
  while(pointer->next != NULL) {
    pointer = pointer->next;
  }
  pointer->next = newelement;

  // show LL
  i=0;
  pointer = head;
  if (pointer == NULL) {
    printf("the LL is empty\n");
  } else {
    while (pointer != NULL) {
      printf("element %d\n  name: %s\n  value: %d\n", i++, pointer->name, pointer->value);
      pointer = pointer-> next;
    }
    printf ("\n");
  }

  // PUSH NEXT element to end of LL
  newelement = malloc(sizeof(T_node));
  memcpy(newelement->name, "!!!!", sizeof(char)*6);
  newelement->value = values++;
  newelement->next = NULL;
  pointer = head;
  while(pointer->next != NULL) {
    pointer = pointer->next;
  }
  pointer->next = newelement;

  // show LL
  i=0;
  pointer = head;
  if (pointer == NULL) {
    printf("the LL is empty\n");
  } else {
    while (pointer != NULL) {
      printf("element %d\n  name: %s\n  value: %d\n", i++, pointer->name, pointer->value);
      pointer = pointer-> next;
    }
    printf ("\n");
  }

  // POP FIRST element LL
  pointer = head;
  if (pointer != NULL) {
    pointer = pointer->next;
  }
  free(head);
  head = pointer;

  // show LL
  i=0;
  pointer = head;
  if (pointer == NULL) {
    printf("the LL is empty\n");
  } else {
    while (pointer != NULL) {
      printf("element %d\n  name: %s\n  value: %d\n", i++, pointer->name, pointer->value);
      pointer = pointer-> next;
    }
    printf ("\n");
  }

  return 0;
}