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

#define USAGE BOLD_UNDERLINE "Usage:" RESET " "
#define OPTIONS BOLD_UNDERLINE "Options:" RESET "\n"
#define HELP_OPTION "  --help    display this help\n"

typedef struct {
  char *argument;
  int (*handler)(int argc, char **argv);
  char *about;
  char *usage;
  char *options;
} command;

static const command commands[] = {
  {"basename", basenamecmd, BASENAME_ABOUT, BASENAME_USAGE, BASENAME_OPTIONS},
  {"clear",    clear,       CLEAR_ABOUT,    CLEAR_USAGE,    ""},
  {"false",    falsecmd,    FALSE_ABOUT,    FALSE_USAGE,    ""},
  {"printenv", printenv,    PRINTENV_ABOUT, PRINTENV_USAGE, PRINTENV_OPTIONS},
  {"pwd",      pwd,         PWD_ABOUT,      PWD_USAGE,      ""},
  {"readlink", readlink,    READLINK_ABOUT, READLINK_USAGE, READLINK_OPTIONS},
  {"rmdir",    rmdirectory, RMDIR_ABOUT,    RMDIR_USAGE,    ""},
  {"sleep",    sleepcmd,    SLEEP_ABOUT,    SLEEP_USAGE,    ""},
  {"sync",     sync,        SYNC_ABOUT,     SYNC_USAGE,     ""},
  {"true",     truecmd,     TRUE_ABOUT,     TRUE_USAGE,     ""},
  {"yes",      yes,         YES_ABOUT,      YES_USAGE,      ""}
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
