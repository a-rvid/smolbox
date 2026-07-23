#ifndef PRINTENV_H
#define PRINTENV_H

#define PRINTENV_ABOUT "Print all environment variables."
#define PRINTENV_USAGE "[OPTION]... [VARIABLE]..."
#define PRINTENV_OPTIONS                                                       \
  "  -0        end each output line with 0 byte rather than newline\n"

int printenv(int argc, char **argv);

#endif
