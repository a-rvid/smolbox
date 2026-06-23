#include <string.h>

#define UNUSED_ARGUMENTS() (void)argc; (void)argv; (void)offset;

char * basename (const char *filename) {
  char *p = strrchr(filename, '/');
  return p ? p + 1 : (char *) filename;
}
