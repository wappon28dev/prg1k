#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define INPUT_MAX 256

int main(int argc, char *argv[])
{
  char input[INPUT_MAX];

  printf("char? ");
  scanf("%s", input);

  int input_len = strlen(input);

  for (int i = 0; i < input_len; i++)
  {
    printf("%c", toupper(input[i]));
  }

  printf("\n");

  return 0;
}
