#include <stdio.h>

int maxOf(int a, int b)
{
  return a > b ? a : b;
}

int main(int argc, char *argv[])
{
  int a, b;

  printf("a b? ");
  scanf("%d %d", &a, &b);

  printf("大きい方の値は %d\n", maxOf(a, b));

  return 0;
}
