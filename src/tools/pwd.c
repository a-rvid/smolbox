#include <stdio.h>
#include <string.h>
#include <string.h>
#include <perror.h>
#include "../lib.h"

int pwd(int argc, char **argv) {
  UNUSED_ARGUMENTS();

  char cwd[PATH_MAX];
  long len = syscall(__NR_getcwd, cwd, sizeof(cwd));
  if (len > 0) {
    cwd[len - 1] = '\n'; // getcwd includes null terminator, replace it
    write(1, cwd, len);
  } else {
    perror(argv[0]);
    return 1;
  }
  return 0;
}
