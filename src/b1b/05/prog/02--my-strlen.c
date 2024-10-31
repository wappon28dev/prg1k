#include <stdio.h>
#include <string.h>

int my_strlen(char *s)
{
  int i = 0;
  while (s[i] != '\0')
  {
    i++;
  }
  return i;
}

int main(int argc, char *argv[])
{
  char str1[128] = "abc";
  char str2[] = "cde";
  char *str3 = "efg";

  printf("my_strlen(str1) = %d\n", my_strlen(str1));
  printf("my_strlen(str2) = %d\n", my_strlen(str2));
  printf("my_strlen(str3) = %d\n", my_strlen(str3));

  return 0;
}
