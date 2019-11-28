#include <stdio.h>
#include <stdlib.h> /* to use malloc */

typedef struct node {
  char name[6];
  char value;
  struct node * next;
} T_node;

int main(void) {

  T_node *newelement, *newelement2;

  newelement = malloc(sizeof(T_node));
  if (newelement == NULL) {
    printf("ERROR: memory could not be allocated\n");
    return 1;
  }

  newelement->value = 3;
  newelement->next = NULL;

  newelement2 = malloc(sizeof(T_node));
  if (newelement2 == NULL) {
    printf("ERROR: memory could not be allocated\n");
    return 1;
  }

  newelement2->value = 7;
  newelement2->next = NULL;

  newelement->next = newelement2;

  free(newelement);
  free(newelement2);

  return 0;
}
