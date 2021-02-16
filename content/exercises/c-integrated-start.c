#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char loremipsum[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam quis nulla velit. Praesent dui augue, luctus sit amet semper sed, auctor eu eros. Maecenas ac urna turpis. Donec rhoncus faucibus scelerisque. Donec sed mollis lectus. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; Proin vitae nunc eleifend, consequat libero quis, feugiat quam. Etiam maximus porta purus. Aliquam facilisis dictum lectus, a molestie elit pharetra a. Nullam tincidunt interdum dui, ut viverra erat. Vivamus eu semper dolor. Etiam ultrices neque urna, maximus semper libero dignissim eu. Morbi aliquam consectetur sagittis. Maecenas nisl leo, rhoncus at commodo eget, accumsan non nisl. Fusce efficitur, nisl a semper varius, leo nisl rutrum sapien, sed imperdiet quam urna ut ipsum. Nam blandit venenatis nibh quis placerat. Sed lobortis est magna, pulvinar feugiat massa mattis vel. Nam fringilla euismod sem ac finibus. Vivamus venenatis orci sit amet justo vulputate cursus. Fusce pellentesque tellus at ipsum gravida, eu ornare turpis vestibulum. Cras dignissim lorem lectus, ut dapibus enim tristique vel. Nam consectetur mi rutrum cursus faucibus. ";
char ipsum[200][200];

void splitIpsum() {
  int n = 0, i, j = 0;
  int found = 0;

  while(!found) {
    if(loremipsum[i] != ' ') {
      ipsum[n][j++] = loremipsum[i];
    } else {
      ipsum[n][j++] = '\0';
      n++;
      j=0;
    }
    if(loremipsum[i] == '\0') {
        found = 1;
    }
    i++;
  }
}

struct page {
  char text[100];
  struct page* next;
};
typedef struct page page;

void printBook(page *bookPtr) {
  if( bookPtr == NULL ) {
    printf("the list is empty\n");
  } else {
    printf("printing the list:\n");
    while( bookPtr != NULL ) {
      printf("  %s\n", bookPtr->text);
      bookPtr = bookPtr->next;
    }
    printf("end of the list\n");
  }
}

void clearBook(page *bookPtr) {
  page *x, *y;

  if( bookPtr == NULL) {
    return;
  }

  while (bookPtr->next != NULL) {
    x = bookPtr;
    y = bookPtr->next;

    while(y->next != NULL) {
      x = y;
      y = y->next;
    }
    x->next=NULL;
    free(y);
  }

  free(bookPtr);
}

page* createRandompage() {
  page* newelement = malloc(sizeof(page));
  strcpy(newelement->text, ipsum[(rand() % 100 + 1)]);
  newelement->next = NULL;

  return newelement;
}

void createRandomBook(int amount, page **ptrHead) {
  srand(time(NULL));
  page* element;
  *ptrHead = createRandompage();
  element = *ptrHead;

  for(int i = 0; i < amount - 1; i++) {
    element->next = createRandompage();
    element = element->next;
  }
}

int main() {
  splitIpsum();

  page* head = NULL;

  printBook(head);
  createRandomBook(10, &head);

  printBook(head);

  clearBook(head);
  head = NULL;

  printBook(head);

  return 0;
}


