#include<unistd.h>
#include<libgen.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<linux/limits.h>

#define PRINT(string) write(1, string, strlen(string));

int pwd() {
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    PRINT(cwd);
  } else {
    perror("getcwd() error");
    return 1;
  }
  return 0;
}

int handler() {
    PRINT("Handler called");
    return 0;
}

typedef struct {
    char* argument;
    int (*handler)(void); // function returning int with void arguments
} command;

static const command commands[] = {
    {"a.out", handler},
    {"pwd", pwd}
};

constexpr size_t num_commands = sizeof(commands) / sizeof(command);

int cmp(const void* a, const void* b) {
    command* ca = (command*)a;
    command* cb = (command*)b;
    return strcmp(ca->argument, cb->argument);
}

int main(int argc, char **argv) {
    command key = {basename(argv[0]), NULL};
    command *result = bsearch(&key, commands, num_commands, sizeof(command), cmp);

    if (result == NULL) {
        PRINT("Command not found\n");
    } else {
        return result->handler();
    }

    return 1;
}
