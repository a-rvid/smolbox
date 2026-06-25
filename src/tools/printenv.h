int printenv(int argc, char **argv, bool offset) {
  UNUSED_ARGUMENTS();
  for (; *environ; ++environ) {
    puts(*environ);
  }
  return 0;
}
