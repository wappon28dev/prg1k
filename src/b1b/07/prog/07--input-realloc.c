#include <errno.h>
#include <stdbool.h>
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

void dump_arr(char *name, int arr[], int arr_length)
{
  for (int i = 0; i < arr_length; i++)
  {
    printf("%s[%i] -> %d\n", name, i, arr[i]);
  }
}

int main(int argc, char *argv[])
{
  int input_length;
  printf("整数の数を入力してください: ");
  scanf("%d", &input_length);

  int *arr = malloc(sizeof(int) * input_length);
  continue_or_handle_malloc_error(arr);

  int arr_length = 0;
  while (true)
  {
    if (arr_length > input_length - 1)
    {
      puts("--- Realloc ---");
      arr = realloc(arr, sizeof(int));
    }

    printf("(%d/%d)\tn? ", arr_length + 1, input_length);
    scanf("%d", &arr[arr_length]);

    if (arr[arr_length] < 0)
    {
      break;
    }

    arr_length++;
  }

  dump_arr("arr", arr, arr_length);

  free(arr);

  return 0;
}
