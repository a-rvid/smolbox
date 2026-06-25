int yes(int argc, char **argv) {
  UNUSED_ARGUMENTS();
  char *print = (argc > 2) ? argv[1] : argv[0];
  for (;;) {
    puts(print);
  }
}
