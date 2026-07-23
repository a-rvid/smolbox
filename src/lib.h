#define PATH_MAX 4096
#define NAME_MAX 255

#define BOLD_UNDERLINE "\e[1;4m"
#define BOLD "\033[1m"
#define RESET "\033[0m"

#define perror(s) my_perror(s)

typedef int (*cmp_func_t)(const void *a, const void *b);

#define UNUSED_ARGUMENTS()                                                     \
  (void)argc;                                                                  \
  (void)argv;
