#include <stdio.h>

int main(int argc, char *argv[])
{
  char array[10 + 1] = {'\0'};

  printf("入力(10文字以内): ");
  scanf("%s", array);

  int i = 0;
  while (array[i] != '\0')
  {
    putchar(array[i]);
    i++;
  }

  puts("");

  return 0;
}
