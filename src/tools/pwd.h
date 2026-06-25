int pwd(int argc, char **argv, bool offset) {
  UNUSED_ARGUMENTS();

  char cwd[PATH_MAX];
  long len = syscall(__NR_getcwd, cwd, sizeof(cwd));
  if (len > 0) {
    cwd[len - 1] = '\n';  // getcwd includes null terminator, replace it
    syscall(__NR_write, 1, cwd, len);
  } else {
    perror("getcwd");
    return 1;
  }
  return 0;
}
