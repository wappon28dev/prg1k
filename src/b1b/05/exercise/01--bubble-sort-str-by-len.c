#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void dump_str_arr(char *arr[], int length)
{
  for (int i = 0; i < length; i++)
  {
    printf("arr[%i] -> %s\n", i, arr[i]);
  }
}

void swap_str_ptr(char **a, char **b)
{
  char *tmp = *a;
  *a = *b;
  *b = tmp;
}

void sort_str_by_len(char **a, char **b)
{
  int a_length = strlen(*a);
  int b_length = strlen(*b);

  bool is_sorted = a_length < b_length;
  if (!is_sorted)
  {
    swap_str_ptr(a, b);
  }
}

void bubble_sort(char *arr[], int length)
{
  for (int i = 0; i < length; i++)
  {
    for (int j = 0; j < length - 1; j++)
    {
      sort_str_by_len(&arr[j], &arr[j + 1]);
    }
  }
}

int main(int argc, char *argv[])
{
  char *list[] = {"hoge", "abc", "xy", "fugagaga"};
  int list_len = sizeof(list) / sizeof(list[0]);

  dump_str_arr(list, list_len);

  bubble_sort(list, list_len);

  puts("--- Sorted by length ---");
  dump_str_arr(list, list_len);

  return 0;
}
