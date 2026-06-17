#include <libgen.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define PRINT(string) write(1, string, strlen(string));
#define PATH_MAX 4096

int ls(int argc, char **argv, bool offset) { return 0; }

int pwd(int argc, char **argv, bool offset) {
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    PRINT(cwd);
  } else {
    perror("getcwd() error");
    return 1;
  }
  return 0;
}

int whoami(int argc, char **argv, bool offset) {
  register struct passwd *pw;
  register uid_t uid;

  uid = geteuid();
  pw = getpwuid(uid);
  if (pw) {
    PRINT(pw->pw_name);
    return 0;
  }
  fprintf(stderr, "cannot find name for user ID %u", uid);
  return 1;
}

typedef struct {
  char *argument;
  int (*handler)(int argc, char **argv,
                 bool offset); // function returning int with void arguments
} command;

#define COMMANDS                                                               \
  X("ls", ls)                                                                  \
  X("pwd", pwd)                                                                \
  X("whoami", whoami)

#define X(argument, handler) {argument, handler},
static const command commands[] = {COMMANDS};
#undef X

#define X(argument, handler) argument " "
static const char help[] = "[ " COMMANDS "]";
#undef X

constexpr size_t num_commands = sizeof(commands) / sizeof(command);

int cmp(const void *a, const void *b) {
  command *ca = (command *)a;
  command *cb = (command *)b;
  return strcmp(ca->argument, cb->argument);
}

int main(int argc, char **argv) {
  for (int i = 0; i < 2; i++) {
    command key = {basename(argv[i]), NULL};
    command *result =
        bsearch(&key, commands, num_commands, sizeof(command), cmp);

    if (result == NULL) {
      if (i == 1) {
        PRINT(help);
      }
    } else {
      return result->handler(argc, argv, i);
    }
  }
  return 1;
}
