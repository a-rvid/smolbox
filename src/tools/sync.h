#include <sys/syscall.h>
#include <unistd.h>

// sync
int sync(int argc, char **argv, bool offset) {
  syscall(SYS_sync);
  return 0;
}
