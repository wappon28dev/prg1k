#include <stdio.h>

int main(int argc, char *argv[])
{
  int x, y;

  printf("(x, y)? ");
  scanf("(%d, %d)", &x, &y);

  printf("(%d, %d) -> (%d, %d)\n", x, y, x * 2, y * 2);

  return 0;
}
