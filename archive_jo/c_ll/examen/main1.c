#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
  char value;
  struct node * prv;
  struct node * nxt;
} T_node;

void showList(T_node *printer) {
  if( printer == NULL ) {
    printf("the list is empty\n");
  } else {
    printf("printing the list: ");
    while( printer != NULL ) {
      printf(" %2d", printer->value);
      printer = printer->nxt;
    }
    printf("\n");
  }
  return;
}


int main(void) {
  int i;
  T_node *head, *newelement, *indicator;

  srand ( time(NULL) );

  newelement = malloc(sizeof(T_node));
  if (newelement == NULL) {
    printf("ERROR: memory could not be allocated\n");
    return 1;
  }
  newelement->value = 0;
  newelement->prv = NULL;
  newelement->nxt = NULL;
  head = newelement;

  showList(head);

  for(i=0;i<10;i++) {
    newelement = malloc(sizeof(T_node));
    if (newelement == NULL) {
      printf("ERROR: memory could not be allocated\n");
      return 1;
    }
    newelement->value = (rand()%10+1);

    indicator = head;
    while( (indicator->value < newelement->value) && (indicator->nxt != NULL) ) {
      indicator = indicator->nxt;
    }

    if(indicator->value < newelement->value) {
      newelement->nxt = indicator->nxt;
      indicator->nxt = newelement;
      newelement->prv = indicator;
      //newelement->nxt->prv = newelement;
    } else {
      indicator = indicator->prv;
      newelement->nxt = indicator->nxt;
      indicator->nxt = newelement;
      newelement->prv = indicator;
    }

    showList(head);
  }

  return 0;
}








































/* l66: newelement->nxt->prv = newelement; */