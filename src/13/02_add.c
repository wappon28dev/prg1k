#include <stdio.h>

int addOf(int a, int b)
{
  return a + b;
}

int main(int argc, char *argv[])
{
  int a = 5;
  int b = 10;

  printf("%d + %d = %d\n", a, b, addOf(a, b));

  return 0;
}
