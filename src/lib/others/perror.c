#include <string.h>
#include <errno.h>

void my_perror(char *s) {
  const char *strerr = strerror(errno);

  struct iovec iov[3] = {
    {s, strlen(s)},
    {": ", 3},
    {(char *)strerr, strlen(strerr)},
  };

  writev(2, iov, 3);
}
