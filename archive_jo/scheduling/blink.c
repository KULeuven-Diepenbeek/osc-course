/* Copyright (c) 2012 Moritz Klammler                                        */
/*                                                                           */
/* Permission is hereby granted, free of charge, to any person obtaining     */
/* a copy of this software and associated documentation files (the           */
/* `Software'), to deal in the Software without restriction, including       */
/* without limitation the rights to use, copy, modify, merge, publish,       */
/* distribute, sublicense, and/or sell copies of the Software, and to        */
/* permit persons to whom the Software is furnished to do so, subject to     */
/* the following conditions:                                                 */
/*                                                                           */
/* The above copyright notice and this permission notice shall be            */
/* included in all copies or substantial portions of the Software.           */
/*                                                                           */
/* THE SOFTWARE IS PROVIDED `AS IS', WITHOUT WARRANTY OF ANY KIND,           */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF        */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                     */
/* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE    */
/* LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION    */
/* OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION     */
/* WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.           */


#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#define PACKAGE "blink-generic"
#define PACKAGE_STRING "blink-generic (unconfigured)"
#define PACKAGE_BUGREPORT ""
#endif

#ifndef COLUMNS
#define COLUMNS 70
#endif

#ifndef CHILDREN_DEFAULT
#define CHILDREN_DEFAULT (35 * COLUMNS / 2)
#endif



#ifndef PERIOD


//#define BLINKY_DEFAULT 1
//#define BLINKY_LOWER 1
#define BLINKY_HIGHER 1


#ifdef BLINKY_DEFAULT
#define PERIOD 4096
#define DEFAULT_PRIORITY 0
#endif

#ifdef BLINKY_LOWER
#define PERIOD 1638400
#define DEFAULT_PRIORITY 19
#endif


#ifdef BLINKY_HIGHER
#define PERIOD 1638400
#define DEFAULT_PRIORITY -20
#endif

#endif

#ifndef DEFAULT_PRIORITY
#define DEFAULT_PRIORITY 0
#endif




/* configure will cause an error if these header files are missing so it is */
/* safe to include them without a macro check. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <sys/resource.h>

const char* program = PACKAGE;
const char* package_string = PACKAGE_STRING;
const char* package_bugreport = PACKAGE_BUGREPORT;
const int children_default = CHILDREN_DEFAULT;
const int period = PERIOD;
const int columns = COLUMNS;

struct args_struct {
  int children;  /* number of child processes to fork */
  int exit;      /* if non-negative, exit immediately with this code */
};

typedef struct args_struct args_t;

/**
 * Parse the command line arguments.
 *
 * @param argc  number of command line arguments
 * @param argv  command line arguments
 * @return      parsed command line arguments
 *
 */
args_t parseArgs(const int argc, const char** argv)
{
  char* endptr;
  args_t args;
  int i;
  args.children = 0;
  args.exit = -1;
  for (i = 0; i < argc; i++)
    {
      if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
        {
          printf("usage: %s [NCHILDREN]\n", program);
          printf("\n");
          printf("Fork NCHILDREN (or %d, by default) processes that each "\
                 "render a\n", children_default);
          printf("terminal cell (two cells, actually) in changing colors.  "\
                 "Do this\n");
          printf("forever.\n");
          printf("\n");
          printf("Options:\n");
          printf("\n");
          printf("--help, -h      show this text and exit\n");
          printf("--version, -v   show the version number and exit\n");
          printf("\n");
          printf("Please send bug reports to <%s>.\n", package_bugreport);
          args.exit = 0;
          return args;
        }
      else if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0)
        {
          printf("%s\n", package_string);
          args.exit = 0;
          return args;
        }
    }
  switch (argc)
    {
    case 1:
      args.children = children_default;
      break;
    case 2:
      args.children = strtol(argv[1], &endptr, 10);
      if (endptr[0])
        {
          fprintf(stderr, "%s: error: unparsable argument `%s'\n",
                  program, argv[1]);
          fprintf(stderr, "usage: %s [NCHILDREN]\n", program);
          args.exit = 2;
        }
      break;
    default:
      fprintf(stderr, "%s: error: wrong number of arguments\n", program);
      fprintf(stderr, "usage: %s [NCHILDREN]\n", program);
      args.exit = 2;
    }
  return args;
}


/**
 * Run an infinite loop and change color of a terminal cell every now and then.
 *
 * @param cell  cell to colorize (running index)
 * @return      0 on success (never happens)
 *
 */
int count(const int cell)
{
  int line = 2 * cell / columns + 1;
  int column = 2 * (cell % (columns / 2)) + 1;
  int color = 0;
  unsigned long i;
  for (i = 0; 1; i++)
    {
      /* It is important to use the unbuffered stderr here. */
      /* Try using stdout to see what I mean. */
      if (i % period == 0)
        {
          color = (color + 1) % 8;
          //color= color % 2;
          fprintf(stderr, "\033[%d;%dH\033[%d;%d;1m%02d\033[m",
                  line, column, color + 40, color + 30, cell % 100);
        }
    }
  return 0;
}


/**
 * Fork child processes that render colorful cells on the terminal.
 *
 * @param argc  number of command line arguments
 * @param argv  command line arguments
 * @return      0 on success (never happens), 1 on error and 2 on user error
 *
 */
int main(const int argc, const char** argv)
{
  args_t args;
  int err;
  int i;
  pid_t pid;
  pid_t* pids;
  int which = PRIO_PROCESS;
  int ret;
  
  args = parseArgs(argc, argv);


  if (args.exit >= 0) { return args.exit; }
  pids = malloc(args.children * sizeof(pid_t));
  if (!pids)
    {
      fprintf(stderr, "%s: error: out of memory\n", program);
      return 1;
    }
  for (i = 0; i < args.children; i++)
    {
      pid = fork();
      switch (pid)
        {
        case -1:
          fprintf(stderr, "%s: error: cannot fork child\n", program);
          return 1;
        case 0:
          /* Act like a child. */
          err = count(i);
          exit(err);
        default:
          pids[i] = pid;
          ret = setpriority(which, pid, DEFAULT_PRIORITY);
        }
    }
  for (i = 0; i < args.children; i++)
    {
      pid = waitpid(pids[i], NULL, 0);
      if (pid == -1) { err = 1; }
    }
  return err;
}