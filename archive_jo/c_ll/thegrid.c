#include <stdio.h>
#include <stdlib.h>

#include "ll_inFunctions2Lib.h"

int weights[6] = {0, 0, 0, 1, 1, 2};

int main(void) {
  char type, naam[10];
  int waarde, prioriteit;
  FILE *fd;

  T_node **queues[3];
  T_node *temp_hoog = NULL, *temp_normaal = NULL, *temp_laag = NULL;

  // prepare the queues
  queues[0]= &temp_hoog;
  queues[1]= &temp_normaal;
  queues[2]= &temp_laag;

  // open file
  fd = fopen("taskpool.txt", "r");
  if (fd == NULL) {
    printf("ERROR opening file 'taskpool.txt'\n");
    return 1;
  }

  // read file up to comments
  // push read task into correct queue
  fscanf(fd, "%s %d %d", naam, &prioriteit, &waarde);
  while (naam[0] != '#'){
    pushToEndOfLL(queues[prioriteit-1], naam, waarde);
    //printf("taak gelezen:\n  naam: %s\n  prioriteit: %d\n  waarde: %d\n\n", naam, prioriteit, waarde);
    fscanf(fd, "%s %d %d", naam, &prioriteit, &waarde);
  }

  fclose(fd);

  // show the queue statuses
  showLL(queues[0]);
  showLL(queues[1]);
  showLL(queues[2]);

  // prepare the scheduler
  prioriteit = 0;

  // while there is work to do
  while( (*(queues[0]) != NULL) || (*(queues[1]) != NULL) || (*(queues[2]) != NULL) ) {

    if( *(queues[weights[(prioriteit)%6]]) != NULL) {
      printf("job %d: ", prioriteit);
      printf("%s\n", (*(queues[weights[(prioriteit)%6]]))->name);
      popFirstFromLL(queues[weights[(prioriteit)%6]]);
    }

    prioriteit++;
  }

  return 0;

}
