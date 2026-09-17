#include <stdbool.h>
#include <execvp.h>
#include <stddef.h>
#include <stdio.h>

int nice(int argc, char **argv) {
  errno = 0;
  int niceness = 20 - syscall(__NR_getpriority, PRIO_PROCESS, 0);
  if (errno != 0) {
    perror("getpriority");
    return 1;
  }

  int opt;

  while ((opt = getopt(argc, argv, "n:")) != -1) {
    switch (opt) {
    case 'n':
      niceness += atoi(optarg);
      break;
    case '?':
      fputs("Unknown option: ", stderr);
      fputc(optopt, stderr);
      fputc('\n', stderr);
      return 2;
    }
  }

  if (argc <= 1) {
    char *sniceness = itoa(niceness);
    puts(sniceness);
    return 0;
  }

  if(syscall(__NR_setpriority, PRIO_PROCESS, 0, niceness) == -1) {
    perror("nice");
    return 1;
  } else {
    if(execvp(argv[1], &argv[1]) == -1) {
      perror(argv[1]);
    };
  }

  return 0;
}
