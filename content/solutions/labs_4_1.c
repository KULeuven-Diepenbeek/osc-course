#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>  /* to use threads */

#define NUMOF_CHILDREN 2
#define MAX_COUNT  5

int main(void) {
  pid_t  pid, ppid;
  int    i;

  if(fork() != 0) {
    pid = getpid();
    for (i = 1; i <= MAX_COUNT; i++) {
      printf("[PARENT] This line is from pid %d, value = %d\n", pid, i);
    }
  } else {
    pid = getpid();
    ppid = getppid();
    for (i = 1; i <= MAX_COUNT; i++) {
      printf("[CHILD from(%d)] This line is from pid %d, value = %d\n", ppid, pid, i);
    } 
  }

  fix this !!

  pthread_t tids[NUMOF_CHILDREN];
  int i;

  for(i=0;i<NUMOF_CHILDREN;i++) {
    pthread_create(&tids[i], NULL, ChildProcess_v2, (void *)(intptr_t)i);
  }

  for(i=0;i<NUMOF_CHILDREN;i++){
    pthread_join(tids[i], NULL);
  }
  
  printf("byebye\n");

  return 0;
}
