int clear(int argc, char **argv, bool offset) {
  UNUSED_ARGUMENTS();
  write(1, "\033[2J\033[H", sizeof("\033[2J\033[H") -1);
  return 0;
}
