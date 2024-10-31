#include <stdio.h>
#include <string.h>

void dump_str(char *str, char *name)
{
  printf("%s = \"%s\"\n", name, str);
}

int main(int argc, char *argv[])
{
  char a[128] = "abc";
  char b[128];

  dump_str(a, "a");
  dump_str(b, "b");

  strcpy(b, a);

  puts("--- Copied ---");
  dump_str(a, "a");
  dump_str(b, "b");

  return 0;
}
