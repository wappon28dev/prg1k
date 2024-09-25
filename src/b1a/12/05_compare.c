#include <stdio.h>

int main(int argc, char *argv[])
{
  int a, b;

  printf("a b? ");
  scanf("%d %d", &a, &b);

  printf("大きい方の値は %d\n", a > b ? a : b);

  return 0;
}
