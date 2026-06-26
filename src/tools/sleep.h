#include <sys/types.h>

#define SLEEP_HELP "Pause for NUMBER seconds.\n\n\
    " BOLD_UNDERLINE "Usage:" RESET " sleep [NUMBER]"

int sleepcmd(int argc, char **argv) {
  UNUSED_ARGUMENTS();
  if (argc < 2) {
    fputs("sleep: missing operand\n", stderr);
    return 1;
  }

  const struct timespec time = {
    .tv_sec = atoi(argv[1]),
    .tv_nsec = 0
  };

  syscall(__NR_clock_nanosleep, 0, 0, &time, NULL);
  return 0;
}
