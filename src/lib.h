#include <string.h>
#include <stddef.h>

#define PATH_MAX 4096
#define NAME_MAX 255

#define BOLD_UNDERLINE "\e[1;4m"
#define RESET "\033[0m"

typedef int (*cmp_func_t)(const void *a, const void *b);

#include "bsearch.h"

#define UNUSED_ARGUMENTS() (void)argc; (void)argv;

void *bsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) {
    return __inline_bsearch(key, base, nmemb, size, compar);
};

/* Force nolibc weak memset to be emitted: compiler synthesizes memset
 * calls from large zero-inits (e.g. char buf[PATH_MAX] = {0}) but on archs
 * without NOLIBC_ARCH_HAS_MEMSET the weak def is pruned before that pass. */
__attribute__((used))
static void *(*const _keep_memset)(void *, int, size_t) = memset;

char * basename (const char *filename) {
  char *p = strrchr(filename, '/');
  return p ? p + 1 : (char *) filename;
}
