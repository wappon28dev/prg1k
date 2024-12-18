#include <stdio.h>

int x(int n)
{
  if (n == 1)
  {
    return 1;
  }

  return x(n - 1) + 2;
}

int main(int argc, const char *argv[])
{
  printf("x_10 = %d\n", x(10));

  return 0;
}
