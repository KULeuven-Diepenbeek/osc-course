#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
  char value;
  struct node* next;
};
typedef struct node node;

void showList(node *printer) {
  if( printer == NULL ) {
    printf("the list is empty\n");
  } else {
    printf("printing the list:\n");
    while( printer != NULL ) {
      printf("  %d\n", printer->value);
      printer = printer->next;
    }
    printf("end of the list\n");
  }
}

void clearList(node *printer) {
  node *x, *y;

  if( printer == NULL) {
    return;
  }

  while (printer->next != NULL) {
    x = printer;
    y = printer->next;

    while(y->next != NULL) {
      x = y;
      y = y->next;
    }
    x->next=NULL;
    free(y);
  }

  free(printer);
}

node* createRandomNode() {
  node* newelement = malloc(sizeof(node));
  newelement->value = (rand() % 10 + 1);
  newelement->next = NULL;

  return newelement;
}

void createListOfItems(int amount, node **ptrHead) {
  srand(time(NULL));
  node* element;
  *ptrHead = createRandomNode();
  element = *ptrHead;

  for(int i = 0; i < amount - 1; i++) {
    element->next = createRandomNode();
    element = element->next;
  }
}

int main() {
  node* head = NULL;

  showList(head);
  createListOfItems(10, &head);

  showList(head);

  clearList(head);
  head = NULL;

  showList(head);

  return 0;
}


