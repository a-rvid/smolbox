#include <stdio.h>
#include <stdbool.h>

int echo(int argc, char **argv) {
  bool newline = true;
  bool interpret = false;
  int opt;
  opterr = 0;

  while ((opt = getopt(argc, argv, "neE")) != -1) {
    switch (opt) {
    case 'n':
      newline = false;
      break;
    case 'e':
      interpret = true;
      break;
    case 'E':
      break;
    case '?':
      optind--;
      goto done;
    }
  }
 done:


  for (int i = optind; i < argc; i++) {
    if (interpret) {
      for (const char *p = argv[i]; *p; p++) {
        if (*p == '\\' && p[1]) {
          // TODO: add octal \x1b and color codes
          switch (*(++p)) {
          case 'n': putchar('\n'); break;
          case 'r': putchar('\r'); break;
          case 't': putchar('\t'); break;
          case 'v': putchar('\v'); break;
          case 'b': putchar('\b'); break;
          case 'f': putchar('\f'); break;
          case 'a': putchar('\a'); break;
          case '\\': putchar('\\'); break;
          default: putchar('\\'); putchar(*p); break;
          }
        } else {
          putchar(*p);
        }
      }
    } else {
      fputs(argv[i], stdout);
    }
    if (i != argc - 1) { putchar(' '); }
  }

  if(newline) {
    putchar('\n');
  }

  return 0;
}
