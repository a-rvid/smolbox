#include <unistd.h>

// TODO: Implement --ignore-fail-on-empty, --parent and --verbose
int rmdirectory(int argc, char **argv, bool offset) {
  UNUSED_ARGUMENTS();
  rmdir(argv[1 + offset]);
  return 0;
}
