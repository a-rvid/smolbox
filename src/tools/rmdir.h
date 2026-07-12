#include <errno.h>
#include <unistd.h>

#define RMDIR_ABOUT "Remove the DIRECTORY(ies), if they are empty."
#define RMDIR_USAGE "DIRECTORY..."

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
