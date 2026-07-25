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
    }
  }
  for (int i = 1; i < argc; i++) {
    fputs(argv[i], stdout);
    if (i != argc - 1) { putchar(' '); }
  }

  if(newline == true) {
    putchar('\n');
  }
  return 0;
}
