#include "../pwd.h"

int whoami(int argc, char **argv, bool offset) {
  UNUSED_ARGUMENTS();
  register struct passwd *pw;
  register uid_t uid;

  uid = geteuid();
  pw = getpwuid(uid);
  if (pw) {
    puts(pw->pw_name);
    return 0;
  }
  /* fprintf(stderr, "cannot find name for user ID %u", uid); */
  return 1;
}
