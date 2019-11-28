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
      printer = printer->prv;
    }
    printf("\n");
  }
  return;
}


int main(void) {
  int i;
  T_node *tail, *newelement, *indicator;

  srand ( time(NULL) );

  newelement = malloc(sizeof(T_node));
  if (newelement == NULL) {
    printf("ERROR: memory could not be allocated\n");
    return 1;
  }
  newelement->value = 10;
  newelement->prv = NULL;
  newelement->nxt = NULL;
  tail = newelement;

  showList(tail);

  for(i=0;i<10;i++) {
    newelement = malloc(sizeof(T_node));
    if (newelement == NULL) {
      printf("ERROR: memory could not be allocated\n");
      return 1;
    }
    newelement->value = (rand()%10+1);

    indicator = tail;
    while( (indicator->value >= newelement->value) && (indicator->prv != NULL) ) {
      indicator = indicator->prv;
    }

    if(indicator->value >= newelement->value) {
      newelement->nxt = indicator;
      newelement->prv = indicator->prv;
      indicator->prv = newelement;
    } else {
      newelement->nxt = indicator->nxt;
      newelement->prv = indicator;
      indicator->nxt = newelement;
      newelement->nxt->prv = newelement; 
    }

    showList(tail);
  }

  return 0;
}



































/* newelement->nxt->prv = newelement;  */