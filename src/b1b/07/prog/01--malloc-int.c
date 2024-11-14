#include <stdio.h>
#include <stdlib.h>

void dump_arr(char *name, int arr[], int arr_length)
{
  for (int i = 0; i < arr_length; i++)
  {
    printf("%s[%i] -> %d\n", name, i, arr[i]);
  }
}

int main(int argc, char *argv[])
{
  int arr_length = 4;
  int *arr = malloc(sizeof(int) * arr_length);

  for (int i = 0; i < arr_length; i++)
  {
    arr[i] = i;
  }

  dump_arr("arr", arr, arr_length);

  free(arr);

  return 0;
}
