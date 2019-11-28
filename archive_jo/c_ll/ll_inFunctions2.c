#include "ll_inFunctions2Lib.h"

int main(void) {
  char values = 10;
  T_node *temp = NULL;
  T_node **head;

  head = &temp;

  showLL(head);                                // show LL
  
  pushToEndOfLL(head, "hello", values++);      // PUSH FIRST element to end of LL
  showLL(head);                                // show LL

  pushToEndOfLL(head, "world", values++);      // PUSH NEXT element to end of LL
  showLL(head);                                // show LL
  
  pushToEndOfLL(head, "!!!!!", values++);      // PUSH NEXT element to end of LL
  showLL(head);                                // show LL

  while(*head != NULL) {
    popFirstFromLL(head);                      // POP FIRST element LL
    showLL(head);                              // show LL
  }

  return 0;
}
