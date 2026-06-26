#include <stdio.h>
#include "getopt.h"
#include <stdlib.h>

#define PRINTENV_ABOUT "Print all environment variables."
#define PRINTENV_USAGE "[OPTION]... [VARIABLE]..."
#define PRINTENV_OPTIONS \
  "  -0        end each output line with 0 byte rather than newline\n"

// NOTE! Printenv should also print the variable
int printenv(int argc, char **argv) {
  UNUSED_ARGUMENTS();
  extern char **environ;
  if (!environ) return 0;
  int newline = true;
  int opt;

  while((opt = getopt(argc, argv, "0")) != -1) {
    switch(opt) {

    case '0':
      newline = false;
      break;
    case '?':
      return 1;
      break;
    }
  }

  if((argc - optind) == 0) {
    for (; *environ; ++environ) {
      fputs(*environ, stdout);

      if(newline) {
          fputc('\n', stdout);
      }
    }
  } else {
    const char *value = getenv(argv[0 + optind]);
    fputs(value, stdout);
    if(newline) {
      fputc('\n', stdout);
    }
  }

  return 0;
}
