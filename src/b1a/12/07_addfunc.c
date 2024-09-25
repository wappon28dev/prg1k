#include <stdio.h>

int add(int a, int b)
{
  return a + b;
}

int main(int argc, char *argv[])
{
  int a, b;

  printf("a b? ");
  scanf("%d %d", &a, &b);

  printf("和は %d\n", add(a, b));

  return 0;
}
