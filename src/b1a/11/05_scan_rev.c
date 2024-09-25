#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char inputText[5 + 1] = {'\0'};

  printf("input: ");
  scanf("%s", inputText);

  for (int i = strlen(inputText); i >= 0; i--)
  {
    putchar(inputText[i]);
  }

  puts("");

  return 0;
}
