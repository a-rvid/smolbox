#include <unistd.h>
#include <errno.h>

// TODO: Implement --ignore-fail-on-empty, --parent and --verbose
int rmdirectory(int argc, char **argv, bool offset) {
  UNUSED_ARGUMENTS();

  if (argc > 1 + offset) {
    if (rmdir(argv[1 + offset]) != 0) {
      perror("rmdir");
    };
  }

  return 0;
}
