#define YES_ABOUT                                                              \
  "Repeatedly output a line with all specified STRING(s), or 'y'."
#define YES_USAGE "[STRING]..."

int yes(int argc, char **argv) {
  for (;;) {
    if (argc >= 2) {
      for (int i = 1; i < argc; i++) {
        fputs(argv[i], stdout);
        if (i != argc - 1) {
          fputc(' ', stdout);
        }
      }
    } else {
      fputc('y', stdout);
    }
    fputc('\n', stdout);
  }
  return 0;
}
