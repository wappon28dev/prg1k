#include <stdio.h>

int main(int argc, char *argv[])
{
  int a, b;

  printf("a b? ");
  scanf("%d %d", &a, &b);

  printf("perimeter = %d\n", 2 * (a + b));
  printf("area = %d\n", a * b);

  return 0;
}
