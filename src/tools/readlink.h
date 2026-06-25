#include <stdio.h>
#include <errno.h>
#include "../getopt.h"

int readlink(int argc, char **argv) {
  int opt;
  bool n = false;
  char returnc;

  while((opt = getopt(argc, argv, "nz")) != -1) {
    switch(opt) {

    case 'n':
      returnc = '\0'; // NOTE: *Technically*, it should print nothing in this case, but it's basically the same for user to have \0
      n = true;
      break;
    case 'z':
      returnc = '\0';
      break;
    case '?':
      return 1;
      break;
    }
  }

  if (n == true && (argc - optind) != 1) {
    returnc = '\n';
  }

  int return_code = 0;

  for (unsigned int i = 0; i < (argc - optind); i++) {
    if (optind + i >= (unsigned)argc) break;
    char out[PATH_MAX] = {0};
    syscall(__NR_readlink, argv[optind + i], out, sizeof(out) -1);

    if (errno != 0) {
      return_code = 1;
      continue;
    }

    fputs(out, stdout);
    putc(returnc, stdout);
  }

  return return_code;
}
