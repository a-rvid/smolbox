#include "../getopt.h"

int basenamecmd(int argc, char **argv, bool offset) {
  int opt;
  bool multiple = false;
  char returnc = '\n';
  char suffix[NAME_MAX] = {0};

  while((opt = mygetopt(argc - offset, argv + offset, "as:z")) != -1) {
    switch(opt) {

    case 'a':
      // Not implemented yet
      multiple = true;
      break;
    case 's':
      strncat(suffix, optarg, sizeof(suffix));
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

  char *out = basename(argv[offset + optind]);
  unsigned int out_len = strlen(out);
  const unsigned int suffix_len = strlen(suffix);

  if (out_len >= suffix_len && strcmp(out + out_len - suffix_len, suffix) == 0) {
    out_len -= suffix_len;
    out[out_len] = '\0';
  }

  struct iovec output[2] = {
    { out, out_len },
    { &returnc, 1 }
  };

  writev(1, output, 2);
  return 0;
}
