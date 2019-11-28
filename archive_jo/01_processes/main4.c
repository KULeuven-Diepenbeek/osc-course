#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(void)
{
  int fd[2], nbytes;
  pid_t pids;
  char string[] = "Hello, world!\n";
  char readbuffer[80];

  pipe(fd);

  /* Start child */
  if((pids = fork()) == -1) {
    perror("fork");
    return 1;
  }

  if(pids == 0) {
    /* CHILD: close input to pipe 0 */
    close(fd[0]);

    /* Send "string" through the output side of pipe */
    write(fd[1], string, (strlen(string)+1));
    return 1;
  } else {
    /* PARENT: closes output to pipe 1 */
    close(fd[1]);

    /* Read in a string from the pipe */
    nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
    printf("Received string: %s", readbuffer);
  }
  
  return(0);
}
