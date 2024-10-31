#include <stdio.h>
#include <string.h>

void dump_str(char *str, char *name)
{
  printf("%s = \"%s\"\n", name, str);
}

void my_strcpy(char *to, char *from)
{
  int i = 0;
  while (from[i] != '\0')
  {
    to[i] = from[i];
    i++;
  }
  to[i] = '\0';
}

int main(int argc, char *argv[])
{
  char a[128] = "abc";
  char b[128];

  dump_str(a, "a");
  dump_str(b, "b");

  my_strcpy(b, a);

  puts("--- Copied ---");
  dump_str(a, "a");
  dump_str(b, "b");

  return 0;
}
