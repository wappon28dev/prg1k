#include <stdio.h>

void dump_arr(int arr[], int length)
{
  for (int i = 0; i < length; i++)
  {
    printf("arr[%i] -> %d\n", i, arr[i]);
  }
}

void set_map_10x(int arr[], int length)
{
  // こっちでは `arr` はポインタとして扱われる → 要素数は算出できない
  for (int i = 0; i < length; i++)
  {
    arr[i] = arr[i] * 10;
  }
}

int main(int argc, char *argv[])
{
  int arr[] = {10, 20, 30, 40, 50};
  int arr_len = sizeof(arr) / sizeof(arr[0]);
  int *p_arr = arr;

  dump_arr(p_arr, arr_len);
  puts("---");

  set_map_10x(p_arr, arr_len);

  dump_arr(p_arr, arr_len);

  return 0;
}
