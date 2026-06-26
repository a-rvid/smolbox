#define PWD_HELP "pwd: pwd\n\
    Print the name of current working directory."

int pwd(int argc, char **argv) {
  UNUSED_ARGUMENTS();

  char cwd[PATH_MAX];
  long len = syscall(__NR_getcwd, cwd, sizeof(cwd));
  if (len > 0) {
    cwd[len - 1] = '\n';  // getcwd includes null terminator, replace it
    write(1, cwd, len);
  } else {
    fputs(argv[0], stderr);
    fputs(strerror(errno), stderr);
    return 1;
  }
  return 0;
}
