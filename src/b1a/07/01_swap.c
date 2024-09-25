#include <stdio.h>

int main(int argc, char *argv[])
{
  int x, y, temp;

  printf("x y? ");
  scanf("%d %d", &x, &y);

  temp = x;
  x = y;
  y = temp;

  printf("%d %d\n", x, y);

  return 0;
}
