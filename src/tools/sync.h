#include <sys/syscall.h>
#include <unistd.h>

// sync
int sync(int argc, char **argv) {
  syscall(__NR_sync);
  return 0;
}
