#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_COUNT  10000
#define NUMOF_CHILDREN 4

void ChildProcess_v2(void) {
  int i, j, isPrime, counter=0;
  pid_t pid = getpid();

  for (i = 2; i <= MAX_COUNT; i++) {
    isPrime = 1;
    for (j = 2; (j <= i/2)&&(isPrime==1); j++) {
      if (i % j==0) {
        isPrime = 0;
      }
    }
    if(isPrime==1) {
      printf("   child (PID=%d) announces that %d is prime.\n", pid, i);
      counter += 1;
    }
  }

  printf("   *** Child process %d is done. Found %d primes under %d. ***\n\n", pid, counter, MAX_COUNT);
  return;
}

int main(void) {
  pid_t pids[NUMOF_CHILDREN], pid;
  int i, n = NUMOF_CHILDREN;
  int retval;

  /* Start children */
  for(i=0;i<NUMOF_CHILDREN;i++) {
    if ((pids[i] = fork()) < 0) {
      perror("fork");
      return 1;
    } else {
      if (pids[i] == 0) {
        ChildProcess_v2();
        exit(0); /* the child process should EXIT and return 0 */
      }
    }
  } // end for

  /* Wait for children */
  while (n > 0) {
    pid = wait(&retval);
    printf("Parent: child with PID %ld exited with status 0x%x.\n", (long)pid, retval);
    // TODO(pts): Remove pid from the pids array.
    --n;
  }

  return 0;
}


