#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char text[20 + 1] = {'\0'};

  printf("input(20文字以下): ");
  scanf("%s", text);

  int aCount = 0;

  for (int i = 0; i < strlen(text); i++)
  {
    if (text[i] == 'a')
    {
      aCount++;
    }
  }

  printf("aの数: %d\n", aCount);

  return 0;
}
