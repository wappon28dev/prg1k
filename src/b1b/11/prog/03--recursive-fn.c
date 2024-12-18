#include <stdio.h>

int x(int n)
{
  if (n == 1 || n == 2)
  {
    return 1;
  }

  return x(n - 1) + x(n - 2);
}

int main(int argc, const char *argv[])
{
  for (int i = 1; i <= 10; i++)
  {
    printf("x_{%2d} = %d\n", i, x(i));
  }

  return 0;
}
