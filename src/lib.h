#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include "bsearch.h"

#define PATH_MAX 4096
#define NAME_MAX 255

#define BOLD_UNDERLINE "\e[1;4m"
#define BOLD "\033[1m"
#define RESET "\033[0m"

#define perror(s) my_perror(s)

void my_perror(const char *s) {
  char *strerr = strerror(errno);

  struct iovec iov[3] = {
    {s, strlen(s)},
    {": ", 3},
    {strerr, strlen(strerr)},
  };

  writev(2, iov, 3);
}

typedef int (*cmp_func_t)(const void *a, const void *b);

#define UNUSED_ARGUMENTS()                                                     \
  (void)argc;                                                                  \
  (void)argv;

char *basename(const char *filename) {
  char *p = strrchr(filename, '/');
  return p ? p + 1 : (char *)filename;
}
