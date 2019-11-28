#include <stdio.h>
#include <stdlib.h> /* to use malloc() & co */
#include <time.h>   /* to use time() */

#define DEBUG 1

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

#if !defined(DEBUG)
  /* seed the random number generator */
  srand ( time(NULL) );
#endif


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
#if !defined(DEBUG)
    newelement->value = (rand()%10+1);
#else
    newelement->value = i;
#endif 
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

  z = head;
  while(z != NULL) {
    if( z->value %2 == 0 ){
      if(flagx == 0) {
        flagx = 1;
        x = z;
        odd = z;
        z = z->next;
        x->next = NULL;
      } else {
        x->next = z;
        z = z->next;
        x = x->next;
        x->next = NULL;
      }
    } else {
      if(flagy == 0) {
        flagy = 1;
        y = z;
        even = z;
        z = z->next;
        y->next = NULL;
      } else {
        y->next = z;
        z = z->next;
        y = y->next;
        y->next = NULL;
      }
    }
  }
  
  head = NULL;
  showList(head);
  showList(odd);
  showList(even);

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