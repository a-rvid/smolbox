#include "lib.h"
#include "tools/basename.h"
#include "tools/yes.h"
#include "tools/sleep.h"
#include "tools/true.h"
#include "tools/false.h"
#include "tools/clear.h"
#include "tools/readlink.h"
#include "tools/rmdir.h"
#include "tools/printenv.h"
#include "tools/sync.h"
#include "tools/pwd.h"

#define EXAMPLE_USAGE "Help command has not been created for this function."

typedef struct {
  char *argument;
  int (*handler)(int argc, char **argv); // function returning int passing arguments
  char *help;
  int help_len;
} command;

static const command commands[] = {
  {"basename", basenamecmd, EXAMPLE_USAGE, sizeof(EXAMPLE_USAGE)},
  {"clear", clear, EXAMPLE_USAGE, sizeof(EXAMPLE_USAGE)},
  {"false", falsecmd, EXAMPLE_USAGE, sizeof(EXAMPLE_USAGE)},
  {"printenv", printenv, EXAMPLE_USAGE, sizeof(EXAMPLE_USAGE)},
  {"pwd", pwd, PWD_HELP, sizeof(PWD_HELP)},
  {"readlink", readlink, EXAMPLE_USAGE, sizeof(EXAMPLE_USAGE)},
  {"rmdir", rmdirectory, EXAMPLE_USAGE, sizeof(EXAMPLE_USAGE)},
  {"sleep", sleepcmd, SLEEP_HELP, sizeof(SLEEP_HELP)},
  {"sync", sync, EXAMPLE_USAGE, sizeof(EXAMPLE_USAGE)},
  {"true", truecmd, EXAMPLE_USAGE, sizeof(EXAMPLE_USAGE)},
  {"yes", yes, EXAMPLE_USAGE, sizeof(EXAMPLE_USAGE)}
};

static const size_t num_commands = sizeof(commands) / sizeof(command);

void command_list(char separator) {
  for (int i = 0; i < (int)num_commands; i++) {
    fputs(commands[i].argument, stdout);
    fputc(separator, stdout);
  }
}

int cmp(const void *a, const void *b) {
  command *ca = (command *)a;
  command *cb = (command *)b;
  return strcmp(ca->argument, cb->argument);
}

int cmdind;
command *enumerate_commands(int argc, char **argv, int times) {
  for (cmdind = 0; cmdind <= times && cmdind < argc; cmdind++) {
    const char *key = basename(argv[cmdind]);
    errno = 0;
    command *result = bsearch(&key, commands, num_commands, sizeof(command), cmp);

    if (result) return result;
  }
  return NULL;
}
