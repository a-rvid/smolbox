#define YES_ABOUT "Repeatedly output a line with all specified STRING(s), or 'y'."
#define YES_USAGE "[STRING]..."

int yes(int argc, char **argv) {
  UNUSED_ARGUMENTS();
  char *print = (argc > 2) ? argv[1] : "y";
  for (;;) {
    puts(print);
  }
}
