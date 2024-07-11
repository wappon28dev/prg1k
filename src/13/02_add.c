#include <stdio.h>

void dumpAddOf(int a, int b)
{
  printf("%d + %d = %d\n", a, b, a + b);
}

int main(int argc, char *argv[])
{
  int a = 5;
  int b = 10;

  dumpAddOf(a, b);

  return 0;
}
