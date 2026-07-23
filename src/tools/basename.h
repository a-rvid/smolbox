#ifndef BASENAME_H
#define BASENAME_H

#define BASENAME_ABOUT                                                         \
  "Print NAME with any leading directory components removed.\nIf specified, "  \
  "also remove a trailing SUFFIX."
#define BASENAME_USAGE "NAME [SUFFIX]\n   or: basename OPTION... NAME..."
#define BASENAME_OPTIONS                                                       \
  "  -a        support multiple arguments and treat each as a NAME\n"          \
  "  -s SUFFIX remove a trailing SUFFIX; implies -a\n"                         \
  "  -z        end each output line with NUL, not newline\n"

int basenamecmd(int argc, char **argv);

#endif
