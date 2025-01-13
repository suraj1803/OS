#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void separate_tokens(char* input, char* dest[], int size) {
  int token = 0;
  char* str = malloc(30);
  int idx = 0;
  int i = 0;
  for (int i = 0; i < 100; i++) {
    if (input[i] == ' ' || input[i] == '\n') {
      str[idx] = '\0';
      dest[token] = malloc(strlen(str) + 1);
      strcpy(dest[token], str);
      idx = 0;
      token++;
      if (input[i] == '\n') {
        break;
      }
    }
    else {
      str[idx] = input[i];
      idx++;
    }
  }

  dest[token] = NULL;

  free(str);
}

int main() {
  char* dest[50];
  char* input = malloc(100);
  fgets(input, 100, stdin);
  /*printf("%d\n", input[strlen(input)]);*/

  separate_tokens(input, dest, 50);

  for (int i = 0; dest[i] != NULL; i++) {
    printf("%s\n", dest[i]);
    free(dest[i]);
  }

  free(input);

  return 0;
}
