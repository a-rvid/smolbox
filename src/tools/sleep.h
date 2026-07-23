#ifndef SLEEP_H
#define SLEEP_H

#define SLEEP_ABOUT "Pause for NUMBER seconds."
#define SLEEP_USAGE "NUMBER"
#define SLEEP_OPTIONS                                                          \
  "Pause for NUMBER seconds, where NUMBER is an integer or floating-point.\n\
SUFFIX may be 's','m','h', or 'd', for seconds, minutes, hours, days."

int sleepcmd(int argc, char **argv);

#endif
