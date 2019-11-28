#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_COUNT  100000
#define NUMOF_CHILDREN 4

void ChildProcess_v1(void);                /* child process prototype  */

void main(void) {
  pid_t pids[NUMOF_CHILDREN], pid;
  int i, n = NUMOF_CHILDREN;
  int retval;

  /* Start children */
  for(i=0;i<NUMOF_CHILDREN;i++) {
    if ((pids[i] = fork()) < 0) {
      perror("fork");
      return;
    } else {
      if (pids[i] == 0) {
        ChildProcess_v1();
        exit(0); /* the child process should EXIT and return 0 */
      }
    }
  } // end for

  /* Wait for children */
  while (n > 0) {
    pid = wait(&retval);
    printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, retval);
    // TODO(pts): Remove pid from the pids array.
    --n;
  }

  return;
}

void ChildProcess_v1(void) {
  int i;
  pid_t pid = getpid();
  for (i = 1; i <= MAX_COUNT; i++) {
    printf("   This line is from child (PID=%d), value = %d\n", pid, i);
  }

  printf("   *** Child process %d is done ***\n", pid);
}


/*

for i in `pgrep test`
do
  sudo renice -n -19 -p $i
done

running time test2: (PR 20, NI 0)
(20 children)
53.276
63
67

*/