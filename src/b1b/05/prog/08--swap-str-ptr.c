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

int main(int argc, char *argv[])
{
  char *a = "AB";
  char *b = "XY";

  dump_str(a, "a");
  dump_str(b, "b");

  swap_str_ptr(&a, &b);

  puts("--- Swapped ---");
  dump_str(a, "a");
  dump_str(b, "b");

  return 0;
}
