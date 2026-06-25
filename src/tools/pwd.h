int pwd(int argc, char **argv, bool offset) {
  UNUSED_ARGUMENTS();
  char cwd[PATH_MAX];
  if (syscall(__NR_getcwd, cwd, sizeof(cwd)) > 0) {
    puts(cwd);
  } else {
    perror("getcwd");
    return 1;
  }
  return 0;
}
