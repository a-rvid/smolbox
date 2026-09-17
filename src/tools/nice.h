#ifndef NICE_H
#define NICE_H

#define NICE_ABOUT                                                             \
  "Run COMMAND with an adjusted niceness, which affects process scheduling.\n" \
  "With no COMMAND, print the current niceness.  Niceness values range from\n" \
  "-20 (most favorable to the process) to 19 (least favorable to the process)."
#define NICE_USAGE "Usage: nice [OPTION] [COMMAND [ARG]...]"
#define NICE_OPTIONS "  -n        add N to the niceness (default is 10)"

int nice(int argc, char **argv);

#endif
