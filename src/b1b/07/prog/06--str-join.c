#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void continue_or_handle_malloc_error(void *ptr)
{
  if (ptr == NULL)
  {
    fprintf(stderr, "メモリの確保に失敗しました: %s\n", strerror(errno));
    exit(1);
  }
}

int main(int argc, char *argv[])
{
  char *str1 = "ABCDE";
  char *str2 = "XYZ";

  char *str = malloc(strlen(str1) + strlen(str2) + 1);
  continue_or_handle_malloc_error(str);

  strcpy(str, str1);
  strcat(str, str2);

  printf("str1: %s\n", str1);
  printf("str2: %s\n", str2);
  printf("str: %s\n", str);

  free(str);

  return 0;
}
