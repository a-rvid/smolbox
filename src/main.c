#include <libgen.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <getopt.h>

#define PATH_MAX 4096

int ls(int argc, char **argv, bool offset) {
  char dirs[argc - 1 - offset];
  bool longer = false, all = false, almost_all = false, human_readable = false;

  static struct option long_options[] = {
    {"long", no_argument, NULL, 'l'},
    {"all", no_argument, NULL, 'a'},
    {"almost-all", no_argument, NULL, 'A'},
    {"human-readable", no_argument, NULL, 'h'},
    {NULL, 0, NULL, 0}
  };
  int opt;
  while ((opt = getopt_long(argc, argv, "laAh", long_options, NULL)) != -1) {
    switch (opt) {
    case 'l':
      longer = true; break;
    case 'a':
      all = true; break;
    case 'A':
      almost_all = true; break;
    case 'h':
      human_readable = true; break;
    }
  }

  /* printf("Long: %d, all: %d, almost all: %d, human readable: %d\n", longer, all, almost_all, human_readable); */

  return 0;
}

int pwd(int argc, char **argv, bool offset) {
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    puts(cwd);
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
    puts(pw->pw_name);
    return 0;
  }
  /* fprintf(stderr, "cannot find name for user ID %u", uid); */
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
        puts(help);
      }
    } else {
      argv[0] = argv[i];
      return result->handler(argc, argv, i);
    }
  }
  return 1;
}
