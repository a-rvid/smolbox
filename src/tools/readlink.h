#ifndef READLINK_H
#define READLINK_H

#define READLINK_ABOUT "Print value of a symbolic link on standard output."
#define READLINK_USAGE "[OPTION]... FILE..."
#define READLINK_OPTIONS                                                       \
  "  -n        do not output the trailing delimiter\n"                         \
  "  -z        end each output line with NUL, not newline\n"

int readlink(int argc, char **argv);

#endif
