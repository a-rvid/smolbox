#include <libgen.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

#define PRINT(string) write(1, string, strlen(string));
#define PATH_MAX 4096

/* #define INDEX (i + 1 + offset) */
int ls(int argc, char **argv, bool offset) {
  char dirs[argc - 1 - offset];
  bool human_readable = false; // --human-readable/-h
  bool all = false; // --all/-a
  bool almost_all = false; // --almost-all/-A
  bool llong = false; // --long/-l
  for (int i = 0; i < (argc - 1 - offset); i++) { // Looping through all args
    if(argv[i + 1 + offset][0] == '-') { // one dash
        if(argv[i + 1 + offset][1] == '-') { // two dashes
            if(strcmp(argv[i + 1 + offset], "--human-readable")) {
                human_readable = true;
            } else if(strcmp(argv[i + 1 + offset], "--all")) {
                all = true;
            } else if(strcmp(argv[i + 1 + offset], "--almost-all")) {
                almost_all = true;
            } else if(strcmp(argv[i + 1 + offset], "--long")) {
                llong = true;
            }
        } else {
          for(int j = 1; j < strlen(argv[i + 1 + offset]) - 1; j++) { // checks all characters after 1 dash
            /* if(argv[i + 1 + offset][j]) */
          }
        }
    printf("%s argument %d", argv[i + 1 + offset], i + 1 + offset);
    }
  }
  printf("%d%d%d%d", human_readable, all, almost_all, llong);
  return 0;
}

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
