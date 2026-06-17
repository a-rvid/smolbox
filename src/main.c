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
#include <argp.h>

#define PRINT(string) write(1, string, strlen(string));
#define PATH_MAX 4096

const char *argp_program_version = "smolbox v0.1.0";
const char *argp_program_bug_address = "<bug@rvid.eu>";
static char args_doc[] = "[FILE]...";

struct arguments_ls {
  bool longer;
  bool all;
  bool almost_all;
  bool human_readable;
};

static error_t parse_opt_ls(int key, char *arg, struct argp_state *state) {
    struct arguments_ls *arguments = state->input;
    switch (key) {
        case 'l': arguments->longer = true; break;
        case 'a': arguments->all = true; break;
        case 'A': arguments->almost_all = true; break;
        case 'h': arguments->human_readable = true; break;
        case ARGP_KEY_ARG: return 0;
        default: return ARGP_ERR_UNKNOWN;
    }
    return 0;
}


static struct argp_option options_ls[] = {
    { "long", 'l', 0, 0, "Display detailed information"},
    { "all", 'a', 0, 0, "Do not ignore hidden files"},
    { "almost-all", 'A', 0, 0, "Only ignore '.' and '..'"},
    { "human-readable", 'h', 0, 0, "With -l, print sizes like 1K 234M 2G etc."},
    { 0 }
};
static char doc_ls[] = "List directory contents.\n"
                       "Ignore files and directories starting with a '.' by default";
/* #define INDEX (i + 1 + offset) */
int ls(int argc, char **argv, bool offset) {
  static struct argp argp = { options_ls, parse_opt_ls, args_doc, doc_ls, 0, 0, 0 };
  char dirs[argc - 1 - offset];
  struct arguments_ls args;

  argp_parse(&argp, argc, argv, 0, 0, &args);
  printf("Long: %d, all: %d, almost all: %d, human readable: %d", args.longer, args.all, args.almost_all, args.human_readable);

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
      argv[0] = argv[i];
      return result->handler(argc, argv, i);
    }
  }
  return 1;
}
