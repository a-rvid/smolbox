int yes(int argc, char **argv, bool offset) {
  UNUSED_ARGUMENTS();
  char *print = (argc > (2 + offset)) ? argv[1 + offset] : "yes";
  for (;;) {
    puts(print);
  }
}
