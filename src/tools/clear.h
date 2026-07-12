#include <unistd.h>

#define CLEAR_ABOUT "Clear the terminal screen."
#define CLEAR_USAGE ""

int clear(int argc, char **argv) {
  UNUSED_ARGUMENTS();
  write(1, "\033[2J\033[H", sizeof("\033[2J\033[H") - 1);
  return 0;
}
