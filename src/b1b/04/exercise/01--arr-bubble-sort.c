#include <stdbool.h>
#include <stdio.h>

void dump_arr(int arr[], int length)
{
  for (int i = 0; i < length; i++)
  {
    printf("arr[%i] -> %d\n", i, arr[i]);
  }
}

void swap(int *p_num1, int *p_num2)
{
  int temp = *p_num1;
  *p_num1 = *p_num2;
  *p_num2 = temp;
}

void sort(int *p_num1, int *p_num2)
{
  bool has_sorted = *p_num1 < *p_num2;
  if (!has_sorted)
  {
    swap(p_num1, p_num2);
  }
}

void bubble_sort(int arr[], int length)
{
  for (int i = 0; i < length; i++)
  {
    for (int j = 0; j < length - 1; j++)
    {
      sort(&arr[j], &arr[j + 1]);
    }
  }
}

int main(int argc, char *argv[])
{
  int arr[] = {1, 5, 3, 2, 4};
  int arr_len = sizeof(arr) / sizeof(arr[0]);

  dump_arr(arr, arr_len);

  bubble_sort(arr, arr_len);

  puts("--- Sorted ---");
  dump_arr(arr, arr_len);

  return 0;
}
