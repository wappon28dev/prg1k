#include <stdio.h>

int main(int argc, char *argv[])
{
  int a = 1;
  int b = 2;

  int *p_a = &a;
  int *p_b = &b;

  printf("%d\n", a);
  printf("%d\n", b);

  *p_a = 3;
  *p_b = 4;

  printf("%d\n", a);
  printf("%d\n", b);

  return 0;
}
