#include <sys/syscall.h>
#include <unistd.h>

// sync
int sync(int argc, char **argv, bool offset) {
  syscall(__NR_sync);
  return 0;
}
