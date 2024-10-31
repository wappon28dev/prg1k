#include <stdio.h>

int main(int argc, char *argv[])
{
  char a[][5] = {"LISP", "C", "Ada"};
  char *p[] = {"PAUL", "X", "MAC"};

  int a_len = sizeof(a) / sizeof(a[0]);
  int p_len = sizeof(p) / sizeof(p[0]);

  for (int i = 0; i < a_len; i++)
  {
    printf("a[%d] = \"%s\"\n", i, a[i]);
  }

  for (int i = 0; i < p_len; i++)
  {
    printf("p[%d] = \"%s\"\n", i, p[i]);
  }

  return 0;
}
