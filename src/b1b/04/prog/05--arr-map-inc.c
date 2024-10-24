#include <stdio.h>
#define LENGTH 5

void dump_arr(int arr[], int length)
{
  for (int i = 0; i < length; i++)
  {
    printf("arr[%i] -> %d\n", i, arr[i]);
  }
}

int main(int argc, char *argv[])
{
  int arr[LENGTH] = {10, 20, 30, 40, 50};
  int *p_arr = arr;

  dump_arr(p_arr, LENGTH);
  puts("---");

  for (int i = 0; i < LENGTH; i++)
  {
    *(p_arr + i) += 1;
    // arr[i] += 1;
  }

  dump_arr(p_arr, LENGTH);

  return 0;
}
