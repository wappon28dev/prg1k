#include <stdio.h>
#include <string.h>

void dump_str(char *str, char *name)
{
  printf("%s = \"%s\"\n", name, str);
}

void swap_str(char *a, char *b)
{
  char tmp[128];
  strcpy(tmp, a);
  strcpy(a, b);
  strcpy(b, tmp);
}

int main(int argc, char *argv[])
{
  char a[128] = "abcde";
  char b[128] = "xyz";

  dump_str(a, "a");
  dump_str(b, "b");

  swap_str(a, b);

  puts("--- Swapped ---");
  dump_str(a, "a");
  dump_str(b, "b");

  return 0;
}
