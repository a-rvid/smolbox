#include <sys/syscall.h>
#include <unistd.h>

#define SYNC_ABOUT "Synchronize cached writes to persistent storage."
#define SYNC_USAGE ""

int sync(int argc, char **argv) {
  (void)argc; (void)argv;
  syscall(__NR_sync);
  return 0;
}
