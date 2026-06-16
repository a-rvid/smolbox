#include <unistd.h>
#include <libgen.h>
#include <string.h>
#include <stdlib.h>

#define PRINT(string) write(1, string, strlen(string));

void pwd() {
  PRINT("pwd");
}

void handler() {
  PRINT("Handler called");
}

typedef struct {
  char* argument;
  void (*handler)(void); // function returning void with void arguments
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
    result->handler();
  }
  return 0;
}
