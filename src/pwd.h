#include <sys/types.h>
#include <stdio.h>

struct passwd {
  char  *pw_name;
  uid_t  pw_uid;
  gid_t  pw_gid;
  char   *pw_dir;
  char   *pw_shell;
};

struct passwd *getpwuid(uid_t uid) {
  struct passwd *pass;

  FILE *file = fopen("/etc/passwd", "r");
  if (!file) return 0;
}
