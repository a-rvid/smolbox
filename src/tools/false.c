#define FALSE_ABOUT "Returns false, an unsuccessful exit status."
#define FALSE_USAGE ""

int falsecmd(int argc, char **argv) {
  (void)argc; (void)argv;
  return 1;
}
