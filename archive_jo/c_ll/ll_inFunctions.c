#include "ll_inFunctionsLib.h"

int main(void) {
  char values = 10;
  T_node *head=NULL;

  showLL(head);                                     // show LL
  
  head = pushToEndOfEmptyLL("hello", values++);     // PUSH FIRST element to end of LL
  showLL(head);                                     // show LL

  pushToEndOfLL(head, "world", values++);           // PUSH NEXT element to end of LL
  showLL(head);                                     // show LL
  
  pushToEndOfLL(head, "!!!!!", values++);           // PUSH NEXT element to end of LL
  showLL(head);                                     // show LL

  while(head != NULL) {
    head = popFirstFromLL(head);                      // POP FIRST element LL
    showLL(head);                                     // show LL
  }

  return 0;
}
