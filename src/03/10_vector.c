#include <stdio.h>

int main(int argc, char *argv[])
{
  char input[256];

  printf("(x,y)? ");
  scanf("%s", input);

  int x, y;
  sscanf(input, "(%d,%d)", &x, &y);

  printf("(%d,%d) -> (%d,%d)\n", x, y, x * 2, y * 2);

  return 0;
}
