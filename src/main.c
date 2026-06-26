#define _NOLIBC_GETOPT_H
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include "tools.h"

#define NAME "SmolBox"
#define VERSION "v0.1.0"

#define PATH_MAX 4096

static const char help[] =
    NAME " version " VERSION "\n\nRegistered commands:";

int main(int argc, char *argv[], char *envp[]) {
  (void)envp;

  command *result = enumerate_commands(argc, argv, 2);
  if (result == NULL) {
    puts(help);
    command_list(' ');
  } else {
    argv += cmdind;
    argc -= cmdind;
    if(strcmp(argv[1], "--help") == 0) {
      write(1, result->help, result->help_len);
      return 0;
    }

    return result->handler(argc, argv);
  }
  command_list(' ');
  return 0;
}
