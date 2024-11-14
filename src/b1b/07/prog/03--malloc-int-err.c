#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dump_arr(char *name, int arr[], int arr_length)
{
  for (int i = 0; i < arr_length; i++)
  {
    printf("%s[%i] -> %d\n", name, i, arr[i]);
  }
}

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
  int arr_length = 4;
  int *arr = malloc(-1); // error

  continue_or_handle_malloc_error(arr);

  for (int i = 0; i < arr_length; i++)
  {
    arr[i] = i;
  }

  dump_arr("arr", arr, arr_length);

  free(arr);

  return 0;
}
