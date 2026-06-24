/* #include <getopt.h> */
/* #include <libgen.h> */
/* #include <errno.h> */
/* #include <pwd.h> */
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
/* #include <stdlib.h> */
/* #include <sys/stat.h> */
/* #include <sys/types.h> */
/* #include <sys/resource.h> */
#include "lib.h"
#include "tools/yes.h"
#include "tools/clear.h"
#include "tools/rmdir.h"

char **environ;

#define NAME "SmolBox"
#define VERSION "v0.1.0"

#define PATH_MAX 4096

/* int ls(int argc, char **argv, bool offset) { */
/*   char dirs[argc - 1 - offset]; */
/*   bool longer = false, all = false, almost_all = false, human_readable = false; */

/*   static struct option long_options[] = { */
/*       {"long", no_argument, NULL, 'l'}, */
/*       {"all", no_argument, NULL, 'a'}, */
/*       {"almost-all", no_argument, NULL, 'A'}, */
/*       {"human-readable", no_argument, NULL, 'h'}, */
/*       {NULL, 0, NULL, 0}}; */
/*   int opt; */
/*   while ((opt = getopt_long(argc, argv, "laAh", long_options, NULL)) != -1) { */
/*     switch (opt) { */
/*     case 'l': */
/*       longer = true; */
/*       break; */
/*     case 'a': */
/*       all = true; */
/*       break; */
/*     case 'A': */
/*       almost_all = true; */
/*       break; */
/*     case 'h': */
/*       human_readable = true; */
/*       break; */
/*     } */
/*   } */

/*   /\* printf("Long: %d, all: %d, almost all: %d, human readable: %d\n", longer, */
/*    * all, almost_all, human_readable); *\/ */

/*   return 0; */
/* } */

/* int niceness(int argc, char **argv, bool offset) { */
/*   errno = 0; */
/*   int niceness = getpriority(PRIO_PROCESS, 0); */
/*   if (errno != 0) { */
/*     perror("getpriority"); */
/*     return 1; */
/*   } */

/*   static struct option long_options[] = { */
/*     {"adjustment", required_argument, NULL, 'n'}, */
/*     {NULL, 0, NULL, 0} */
/*   }; */

/*   int outnice = niceness; */
/*   int opt; */

/*   char *fake_argv[3] = {NULL}; */
/*   fake_argv[0] = argv[0]; */
/*   fake_argv[1] = argv[1+offset]; */
/*   // Segmentation Fault here!!! */
/*   if ((opt = getopt_long(2, fake_argv, "n:", long_options, NULL)) == 'n') { */
/*     outnice += atoi(optarg); */
/*   } else { */
/*     outnice += 10; */
/*   } */

/*   if (argc <= 1 + offset) { */
/*     char sniceness[4]; */
/*     Itoa(niceness, sniceness, 10); */
/*     puts(sniceness); */
/*     return 0; */
/*   } */

/*   if(setpriority(PRIO_PROCESS, 0, outnice) == -1) { */
/*     perror("nice"); */
/*     return 1; */
/*   } else { */
/*     if(execvp(argv[1 + offset], &argv[1 + offset]) == -1) { */
/*       perror(argv[1 + offset]); */
/*     }; */
/*   } */

/*   return 0; */
/* } */

/* int printenv(int argc, char **argv, bool offset) { */
/*   extern char **environ; */
/*   for (environ; *environ; ++environ) { */
/*     puts(*environ); */
/*   } */
/*   return 0; */
/* } */

/* int pwd(int argc, char **argv, bool offset) { */
/*   char cwd[PATH_MAX]; */
/*   if (getcwd(cwd, sizeof(cwd)) != NULL) { */
/*     puts(cwd); */
/*   } else { */
/*     perror("getcwd error"); */
/*     return 1; */
/*   } */
/*   return 0; */
/* } */


/* int whoami(int argc, char **argv, bool offset) { */
/*   register struct passwd *pw; */
/*   register uid_t uid; */

/*   uid = geteuid(); */
/*   pw = getpwuid(uid); */
/*   if (pw) { */
/*     puts(pw->pw_name); */
/*     return 0; */
/*   } */
/*   /\* fprintf(stderr, "cannot find name for user ID %u", uid); *\/ */
/*   return 1; */
/* } */

typedef struct {
  char *argument;
  int (*handler)(int argc, char **argv,
                 bool offset); // function returning int with arguments
} command;

#define COMMANDS                                                               \
  X("clear", clear)                                                            \
  X("rmdir", rmdirectory)                                                      \
  X("yes", yes)
  /* X("ls", ls)                                                                  \ */
  /* X("nice", niceness)                                                          \ */
  /* X("printenv", printenv)                                                      \ */
  /* X("pwd", pwd)                                                                \ */
  /* X("rmdir", rmdirectory)                                                      \ */
  /* X("whoami", whoami)                                                          \ */

#define X(argument, handler) {argument, handler},
static const command commands[] = {COMMANDS};
#undef X

#define X(argument, handler) argument " "
static const char help[] =
    NAME " version " VERSION "\n\nRegistered commands: " COMMANDS;
#undef X

static const size_t num_commands = sizeof(commands) / sizeof(command);

int cmp(const void *a, const void *b) {
  command *ca = (command *)a;
  command *cb = (command *)b;
  return strcmp(ca->argument, cb->argument);
}

int main(int argc, char *argv[], char *envp[]) {
  for (int i = 0; i < 2 && i < argc; i++) {
    const char *key = basename(argv[i]);
    errno = 0;
    command *result = bsearch(&key, commands, num_commands, sizeof(command), cmp);

    if (result == NULL) {
      if (i == 1) {
        puts(help);
      }
    } else {
      argv[0] = argv[i];
      return result->handler(argc, argv, i);
    }
  }
  return 0;
}
