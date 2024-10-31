#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char *str = "abcd";
  int length = strlen(str);

  for (int i = 0; i < length; i++)
  {
    printf("%c\n", str[i]);
  }

  return 0;
}
