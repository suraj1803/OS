#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h> 
#define MAX_LINE 80

int AND_ENCOUNTERED = 0;

int separate_tokens(char* input, char* dest[], int size);
void free_args(char* args[]);

int main() {
  int arg_len = MAX_LINE / 2 + 1;
  char* args[arg_len];
  int should_run = 1;


  while (should_run) {
    printf("suraj-> ");
    fflush(stdout);

    char input[MAX_LINE];
    fgets(input, MAX_LINE, stdin);

    int tokens = separate_tokens(input, args, arg_len);

    if (strcmp(args[0], "exit") == 0) {
      should_run = 0;
      free_args(args);
      continue;
    }

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

int separate_tokens(char* input, char* dest[], int size) {
  int token = 0;
  char* str = malloc(30);
  int idx = 0;
  int i = 0;
  int IN = 0;
  while (token < size - 1) {
    if (input[i] == ' ' || input[i] == '\n') {
      if (IN) {
        str[idx] = '\0';
        dest[token] = malloc(strlen(str) + 1);
        strcpy(dest[token], str);
        idx = 0;
        token++;
        IN = 0;
        if (input[i] == '\n') {
          break;
        }
      }
      if (input[i] == '\n') {
        break;
      }
    }
    else {
      if (input[i] == '&') {
        AND_ENCOUNTERED = 1;
        i++;
        continue;
      }
      IN = 1;
      str[idx] = input[i];
      idx++;
    }
    i++;
  }

  dest[token] = NULL;
  free(str);
  return token + 1;
}

void free_args(char* args[]) {
  int i = 0;
  while (args[i] != NULL) {
    free(args[i]);
    i++;
  }
}

void remove_spaces(char* s) {
  char* d = s;
  do {
    while (*d == ' ') {
      ++d;
    }
  } while ((*s++ = *d++));
}
