#include <stdio.h>
#include <stdlib.h> /* to use malloc() & co */

/* define the struct */
typedef struct node {
  char value[100];
  long values[100];
  struct node * next;
} T_node;

int x (int y) {
  printf("%d ", y);
  return x(++y);
}

int main(void) {
  char choice;
  int i;
  T_node *head;

  printf("Dear user\nPlease select how this program should be killed\n");
  printf("\tkilled due to stack overflow (s)\n");
  printf("\tkilled due to heap overflow (h)\n");
  printf("  choose my destiny: ");
  scanf("%c", &choice);

  if (choice != 's' && choice != 'h') {
    printf("ERROR: incorrect input (%c)\n", choice);
    return 1;
  }

  printf("interesting: %c\n", choice);

  if(choice == 's') {
    x(12);
  } 

  if(choice == 'h') {
    while(1) {
      head = malloc(sizeof(T_node));
    }
  } 


  return 0;

}
