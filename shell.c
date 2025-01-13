#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#define MAX_LINE 80

void separate_tokens(char* input, char* dest[], int size);
void free_args(char* args[]);

int main() {
  int arg_len = MAX_LINE / 2 + 1;
  char* args[arg_len];
  int should_run = 1;

  while (should_run) {
    printf("suraj $ ");
    fflush(stdout);

    char input[MAX_LINE];
    fgets(input, MAX_LINE, stdin);

    if (strcmp(input, "exit\n") == 0) {
      should_run = 0;
      continue;
    }

    separate_tokens(input, args, arg_len);

    if (fork() == 0) {
      execvp(args[0], args);
    }
    else {
      wait(NULL);
    }

    free_args(args);
  }

  return 0;
}

void separate_tokens(char* input, char* dest[], int size) {
  int token = 0;
  char* str = malloc(30);
  int idx = 0;
  int i = 0;
  int IN = 0;
  int OUT = 1;
  while (token < size - 1) {
    if (input[i] == ' ' || input[i] == '\n') {
      if (IN && !OUT) {
        str[idx] = '\0';
        dest[token] = malloc(strlen(str) + 1);
        strcpy(dest[token], str);
        idx = 0;
        token++;
        IN = 0;
        OUT = 1;
        if (input[i] == '\n') {
          break;
        }
      }
        if (input[i] == '\n') {
          break;
        }
    }
    else {
      OUT = 0;
      IN = 1;
      str[idx] = input[i];
      idx++;
    }

    i++;
  }

  dest[token] = NULL;

  free(str);
}

void free_args(char* args[]) {
    int i = 0;
    while (args[i]) {
      free(args[i++]);
    }
}
