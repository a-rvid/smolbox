#include "lib.h"
#include "tools/basename.h"
#include "tools/yes.h"
#include "tools/sleep.h"
#include "tools/true.h"
#include "tools/false.h"
#include "tools/clear.h"
#include "tools/rmdir.h"
#include "tools/printenv.h"
#include "tools/sync.h"
#include "tools/pwd.h"

typedef struct {
  char *argument;
  int (*handler)(int argc, char **argv,
                 bool offset); // function returning int with arguments
} command;

static const command commands[] = {
  {"basename", basenamecmd},
  {"clear", clear},
  {"false", falsecmd},
  {"printenv", printenv},
  {"pwd", pwd},
  {"rmdir", rmdirectory},
  {"sleep", sleepcmd},
  {"sync", sync},
  {"true", truecmd},
  {"yes", yes}
};

static const size_t num_commands = sizeof(commands) / sizeof(command);

void command_list(char separator) {
  for (int i = 0; i < num_commands; i++) {
    fputs(commands[i].argument, stdout);
    fputc(separator, stdout);
  }
}
