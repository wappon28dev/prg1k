#include <stdio.h>

int subOf(int a, int b)
{
  return a - b;
}

int main(int argc, char *argv[])
{
  int a = 5;
  int b = 10;

  printf("%d - %d = %d\n", a, b, subOf(a, b));

  return 0;
}
