#include <stdio.h>
#include <stdlib.h> /* to use malloc() & co */

/* define the struct */
typedef struct node {
  char value;
  struct node * next;
} T_node;

/* prototypes */
void showList(T_node *printer);
void clearList(T_node **a);
void initialiseList(T_node ** a, short size);
void pushList(T_node ** a, short value);
short popList(T_node ** a);



int main(void) {
  short i;

  T_node *stackpointer;
  stackpointer = NULL;

  initialiseList(&stackpointer, 5);
  showList(stackpointer);

  pushList(&stackpointer, 5);
  showList(stackpointer);

  i = popList(&stackpointer);
  printf("popped value: %d\n", i);
  showList(stackpointer);

  i = popList(&stackpointer);
  printf("popped value: %d\n", i);
  showList(stackpointer);

  i = popList(&stackpointer);
  printf("popped value: %d\n", i);
  showList(stackpointer);

  i = popList(&stackpointer);
  printf("popped value: %d\n", i);
  showList(stackpointer);

  i = popList(&stackpointer);
  printf("popped value: %d\n", i);
  showList(stackpointer);

  clearList(&stackpointer);
  showList(stackpointer);

  return 0;
}



void initialiseList(T_node ** a, short size) {
  short i;
  T_node *newelement;

  /* create a linked list with size elements*/
  for(i=1;i<size;i++) {
    // make an object
    newelement = malloc(sizeof(T_node));
    if (newelement == NULL) {
      printf("ERROR: memory could not be allocated\n");
      return;
    }

    // initialise the object
    newelement->value = i;
    newelement->next = NULL;
    
    // append the object to the list
    if (*a == NULL) {
      *a = newelement;
    } else {
      newelement->next = *a;
      *a = newelement;
    }
  }
}

void pushList(T_node ** a, short value) {
  short i;
  T_node *newelement;

  // make an object
  newelement = malloc(sizeof(T_node));
  if (newelement == NULL) {
    printf("ERROR: memory could not be allocated\n");
    return;
  }

  // initialise the object
  newelement->value = value;
  newelement->next = *a;
  
  // prepend the object to the list
  *a = newelement;
}

short popList(T_node ** a) {
  short i;

  if(*a == NULL) {
    return -1;
  } else {
    i = (*a)->value;
    *a = (*a)->next;
    return i;
  }
}

void showList(T_node *a) {
  if( a == NULL ) {
    printf("the list is empty\n");
  } else {
    printf("printing the list:\n");
    while( a != NULL ) {
      printf("  %d\n", a->value);
      a = a->next;
    }
    printf("end of the list\n");
  }

  return;
}

void clearList(T_node **a) {
  T_node *element, *element2;

  if( *a == NULL ) {
    return;
  }

  element = *a;

  while(element->next != NULL) {
    element2 = element->next;
    free(element);
    element = element2;
  }

  *a = NULL;

  return;
}
