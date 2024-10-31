#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void dump_str(char *str, char *name)
{
  printf("%s = \"%s\"\n", name, str);
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

int main(int argc, char *argv[])
{
  char *a = "abcde";
  char *b = "xyz";

  dump_str(a, "a");
  dump_str(b, "b");

  sort_str_by_len(&a, &b);

  puts("--- Sorted by length ---");
  dump_str(a, "a");
  dump_str(b, "b");

  return 0;
}
