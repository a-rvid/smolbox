#define _NOLIBC_GETOPT_H
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include "tools.h"

#define NAME "SmolBox"
#define VERSION "v0.1.0"

#define PATH_MAX 4096

#ifndef SMOL_TINY
static const char help[] =
    NAME " version " VERSION "\n\nRegistered commands:";
#endif

int main(int argc, char *argv[], char *envp[]) {
  (void)envp;

  command *result = enumerate_commands(argc, argv, 2);
  if (result == NULL) {
#ifndef SMOL_TINY
    puts(help);
#endif
    command_list(' ');
  } else {
    argv += cmdind;
    argc -= cmdind;
#ifndef SMOL_TINY
    if(argc > 1 && strcmp(argv[1], "--help") == 0) {
      size_t usage_len = strlen(result->usage);
      struct iovec iov[] = {
        { result->about,   strlen(result->about) },
        { "\n\n",          2 },
        { USAGE,           sizeof(USAGE) - 1 },
        { argv[0],         strlen(argv[0]) },
        { " ",             usage_len ? 1 : 0 },
        { result->usage,   usage_len },
        { "\n\n",          2 },
        { OPTIONS,         sizeof(OPTIONS) - 1 },
        { result->options, strlen(result->options) },
        { HELP_OPTION,     sizeof(HELP_OPTION) - 1 },
      };
      writev(1, iov, sizeof(iov) / sizeof(iov[0]));
      return 0;
    }
#endif

    return result->handler(argc, argv);
  }
  command_list(' ');
  return 0;
}
