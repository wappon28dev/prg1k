#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char str1[128] = "abc";
  char str2[] = "cde";
  char *str3 = "efg";

  printf("strlen(str1) = %d\n", (int)strlen(str1));
  printf("strlen(str2) = %d\n", (int)strlen(str2));
  printf("strlen(str3) = %d\n", (int)strlen(str3));

  printf("sizeof(str1) = %d\n", (int)sizeof(str1));
  printf("sizeof(str2) = %d\n", (int)sizeof(str2));
  printf("sizeof(str3) = %d\n", (int)sizeof(str3));

  return 0;
}
