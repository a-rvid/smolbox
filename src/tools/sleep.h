#include <sys/types.h>

int sleepcmd(int argc, char **argv, bool offset) {
  UNUSED_ARGUMENTS();
  if (argc < 2 + offset) {
    fputs("sleep: missing operand\n", stderr);
    return 1;
  }

  const struct timespec time = {
    .tv_sec = atoi(argv[1 + offset]),
    .tv_nsec = 0
  };

  syscall(__NR_clock_nanosleep, 0, 0, &time, NULL);
  return 0;
}
