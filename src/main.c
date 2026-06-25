#define _NOLIBC_GETOPT_H
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include "tools.h"

#define NAME "SmolBox"
#define VERSION "v0.1.0"

#define PATH_MAX 4096

int cmp(const void *a, const void *b) {
  command *ca = (command *)a;
  command *cb = (command *)b;
  return strcmp(ca->argument, cb->argument);
}

static const char help[] =
    NAME " version " VERSION "\n\nRegistered commands:";

int main(int argc, char *argv[], char *envp[]) {
  (void)envp;
  for (int i = 0; i < 2 && i < argc; i++) {
    const char *key = basename(argv[i]);
    errno = 0;
    command *result = bsearch(&key, commands, num_commands, sizeof(command), cmp);

    if (result == NULL) {
      if (i == 1) {
        puts(help);
        command_list(' ');
        return 127;
      }
    } else {
      argv[0] = argv[i];
      return result->handler(argc, argv, i);
    }
  }
  command_list(' ');
  return 0;
}
