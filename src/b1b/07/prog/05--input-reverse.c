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
  int arr_length;
  printf("整数の数を入力してください: ");
  scanf("%d", &arr_length);

  int *arr = malloc(sizeof(int) * arr_length);
  continue_or_handle_malloc_error(arr);

  for (int i = 0; i < arr_length; i++)
  {
    printf("(%d/%d)\tn? ", i + 1, arr_length);
    scanf("%d", &arr[i]);
  }

  puts("--- Reverse ---");
  for (int i = arr_length - 1; i >= 0; i--)
  {
    printf("arr[%i] -> %d\n", i, arr[i]);
  }

  free(arr);

  return 0;
}
