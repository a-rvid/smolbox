int printenv(int argc, char **argv, bool offset) {
  UNUSED_ARGUMENTS();
  if (!environ) return 0;
  for (; *environ; ++environ) {
    puts(*environ);
  }
  return 0;
}
