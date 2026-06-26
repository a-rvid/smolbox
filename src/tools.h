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
#ifndef SMOL_TINY
  char *about;
  char *usage;
  char *options;
#endif
} command;

#ifdef SMOL_TINY
#define CMD(n,h,a,u,o) {n, h}
#else
#define CMD(n,h,a,u,o) {n, h, a, u, o}
#endif

static const command commands[] = {
  CMD("basename", basenamecmd, BASENAME_ABOUT, BASENAME_USAGE, BASENAME_OPTIONS),
  CMD("clear",    clear,       CLEAR_ABOUT,    CLEAR_USAGE,    ""),
  CMD("false",    falsecmd,    FALSE_ABOUT,    FALSE_USAGE,    ""),
  CMD("printenv", printenv,    PRINTENV_ABOUT, PRINTENV_USAGE, PRINTENV_OPTIONS),
  CMD("pwd",      pwd,         PWD_ABOUT,      PWD_USAGE,      ""),
  CMD("readlink", readlink,    READLINK_ABOUT, READLINK_USAGE, READLINK_OPTIONS),
  CMD("rmdir",    rmdirectory, RMDIR_ABOUT,    RMDIR_USAGE,    ""),
  CMD("sleep",    sleepcmd,    SLEEP_ABOUT,    SLEEP_USAGE,    ""),
  CMD("sync",     sync,        SYNC_ABOUT,     SYNC_USAGE,     ""),
  CMD("true",     truecmd,     TRUE_ABOUT,     TRUE_USAGE,     ""),
  CMD("yes",      yes,         YES_ABOUT,      YES_USAGE,      "")
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
