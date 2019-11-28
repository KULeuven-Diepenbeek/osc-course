#include <stdio.h>
#include <stdlib.h> /* to use malloc */

typedef struct node {
  char value;
  struct node * next;
} T_node;


void showLL(T_node **a) {
  T_node * pointer;
  pointer = *a;

  if (pointer == NULL) {
    printf("the LL is empty\n");
  } else {
    printf ("values: ");
    while (pointer != NULL) {
      printf("%02x, ",pointer->value);
      pointer = pointer-> next;
    }
    printf ("\n");
  }
}

void addElementToLL(T_node **a, char b) {
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

}

int main(void) {
  char x = 10;
  T_node *head = NULL;
  T_node **temp = NULL;

  temp = &head;
  showLL(temp);

  addElementToLL(temp, x++);
  showLL(temp);

  addElementToLL(temp, x++);
  showLL(temp);

  addElementToLL(temp, x++);
  showLL(temp);

  return 0;
}