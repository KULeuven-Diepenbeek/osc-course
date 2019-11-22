#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define  MAX_COUNT  5

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

  return 0;
}
