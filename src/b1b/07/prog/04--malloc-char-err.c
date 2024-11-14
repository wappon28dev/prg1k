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
  int arr_length = 5;
  char *arr = malloc(-1); // error

  continue_or_handle_malloc_error(arr);

  strcpy(arr, "hoge");

  for (int i = 0; i < arr_length; i++)
  {
    printf("arr[%i] -> %c\n", i, arr[i]);
  }

  free(arr);

  return 0;
}
