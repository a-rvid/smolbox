#include <string.h>

#define SYS_sync 162

typedef int (*cmp_func_t)(const void *a, const void *b);

#include "bsearch.h"

#define UNUSED_ARGUMENTS() (void)argc; (void)argv; (void)offset;

void *bsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) {
    return __inline_bsearch(key, base, nmemb, size, compar);
};

char * basename (const char *filename) {
  char *p = strrchr(filename, '/');
  return p ? p + 1 : (char *) filename;
}
