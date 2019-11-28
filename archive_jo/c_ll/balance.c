#include <stdio.h>
#include <stdlib.h> /* to use malloc() & co */
#include <time.h>   /* to use time() */

/* define the struct */
typedef struct node {
  char value;
  struct node * next;
} T_node;

/* prototypes */
void showList(T_node *printer);
void clearList(T_node *printer);

int main(void) {
  int i;
  int flagx=0, flagy = 0;

  T_node *head, *tail, *newelement, *x, *y, *z, *odd, *even;
  head = NULL;

  /* seed the random number generator */
  srand ( time(NULL) );

  showList(head);

  /* create a linked list with 10 elements*/
  for(i=1;i<11;i++) {
    // make an object
    newelement = malloc(sizeof(T_node));
    if (newelement == NULL) {
      printf("ERROR: memory could not be allocated\n");
      return 1;
    }

    // initialise the object
    newelement->value = (rand()%10+1);
    newelement->next = NULL;
    
    // append the object to the list
    if (head==NULL) {
      head = newelement;
      tail = newelement;
    } else {
      tail->next = newelement;
      tail = tail->next;
    }
  }

  showList(head);

  clearList(head);
  head = NULL;
  tail = NULL;

  showList(head);

  return 0;
}


void showList(T_node *printer) {
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

  return;
}

void clearList(T_node *printer) {
  T_node *x, *y;

  if( printer == NULL ) {
    // nothing to be done here
    return;
  }

  // free the objects
  while (printer->next != NULL) {
    // start at the beginning of the list
    x = printer;
    y = printer->next;

    // scroll to the end
    while(y->next != NULL) {
      x = y;
      y = y->next;
    }
    // remove final item
    x->next=NULL;
    free(y);
  }

  // free the final object
  free(printer);
  printer = NULL;

  return;
}
