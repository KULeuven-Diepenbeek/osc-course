#include <stdio.h>
#include <pthread.h> /* to use threads */

#include "LL.h"

#define NUMOF_THREADS 5


int checkIfPrime(int a);


int main(void) {
  T_node *head = NULL;
  T_node **temp = NULL;
  int i, rv; 

  pthread_t tid[NUMOF_PHILOSOPHERS+1];

  temp = &head;

  //pthread_create(&tid[j], NULL, checkIfPrime, (void *)(intptr_t)j);

//  for(i=2;i<10000;i++) {
  for(i=2000000;i<3000000;i++) {
    rv = checkIfPrime(i);
    if(rv == 1){
      addElementToLL(temp, i);
    }
  }

  showLL(temp);

  return 0;
}







int checkIfPrime(int a) {
  int keeprunning=1, j;

  for(j=2;(j<a)&&(keeprunning==1);j++) {
    if(a%j == 0) {
      keeprunning = 0;
    }
  }

  return keeprunning;
}