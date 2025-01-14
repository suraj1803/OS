#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void remove_spaces(char* s) {
  char* d = s;
  int IN = 0;
  int OUT = 1;
  do {
    if (*d != ' ') {
      IN = 1;
      OUT = 0;
    }
    while (*d == ' ') {
      if (!IN && OUT) {
        d++;
      }
      else {
        IN = 0;
        OUT = 1;
      }
    }
  } while ((*s++ = *d++));
}

int main() {
  char* dest[50];
  char* input = malloc(100);
  fgets(input, 100, stdin);
  /*printf("%d\n", input[strlen(input)]);*/

  remove_spaces(input);
  /*separate_tokens(input, dest, 50);*/
  printf("%s", input);

  /*for (int i = 0; dest[i] != NULL; i++) {*/
  /*  printf("%s\n", dest[i]);*/
  /*  free(dest[i]);*/
  /*}*/

  free(input);

  return 0;
}
