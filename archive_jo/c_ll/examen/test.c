#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(void) {

  pid_t pids;

  if((pids = fork()) == -1) {
    perror("fork");
    return 1;
  }

  if (pids == 0) { /* child process */
    fork();
  }
  printf("e\n");
  fork();
}
