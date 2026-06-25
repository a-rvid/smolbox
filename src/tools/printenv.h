int printenv(int argc, char **argv) {
  UNUSED_ARGUMENTS();
  extern char **environ;
  if (!environ) return 0;
  for (; *environ; ++environ) {
    puts(*environ);
  }
  return 0;
}
