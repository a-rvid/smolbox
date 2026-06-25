#include <unistd.h>
#include <errno.h>

// TODO: Implement --ignore-fail-on-empty, --parent and --verbose
int rmdirectory(int argc, char **argv) {
  UNUSED_ARGUMENTS();

  if (argc > 1) {
    if (rmdir(argv[1]) != 0) {
      fputs(argv[0], stderr);
      fputs(strerror(errno), stderr);
    };
  }

  return 0;
}
