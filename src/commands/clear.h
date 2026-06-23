int clear(int argc, char **argv, bool offset) {
  UNUSED_ARGUMENTS();
  fputs("\033[2J\033[H", stdout);
  return 0;
}
