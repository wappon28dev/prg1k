#include <stdio.h>

int main(int argc, char *argv[])
{
  char array[10 + 1] = {'\0'};

  printf("入力(10文字以内): ");
  scanf("%s", array);

  for (int i = 0; i < sizeof(array); i++)
  {
    putchar(array[i]);
  }

  puts("");

  return 0;
}
