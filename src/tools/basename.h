#include "../getopt.h"
#include <stdio.h>

int basenamecmd(int argc, char **argv) {
  int opt;
  bool multiple = false;
  char returnc = '\n';

  while((opt = getopt(argc, argv, "azs:")) != -1) {
    switch(opt) {

    case 'a':
      // Not implemented yet
      multiple = true;
      break;
    case 's':
      multiple = true;
      break;
    case 'z':
      returnc = '\0';
      break;
    case ':':
      puts("option needs a value\n");
      break;
    case '?':
      return 1;
      break;
    }
  }

  const unsigned int paths = multiple ? argc - optind : 1;
  const unsigned int suffix_len = optarg ? strlen(optarg) : 0;

  for (unsigned int i = 0; i < paths; i++) {
    if (optind + i >= (unsigned)argc) break;
    char *out = basename(argv[optind + i]);
    unsigned int out_len = strlen(out);

    if (suffix_len && out_len >= suffix_len && strcmp(out + out_len - suffix_len, optarg) == 0) {
        out_len -= suffix_len;
        out[out_len] = '\0';
    }

    fputs(out, stdout);
    putc(returnc, stdout);
  }

  return 0;
}
