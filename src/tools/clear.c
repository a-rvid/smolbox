#include <unistd.h>

int clear(int argc, char **argv) {
  (void)argc; (void)argv;
  write(1, "\033[2J\033[H", sizeof("\033[2J\033[H") - 1);
  return 0;
}
