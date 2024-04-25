#include <stdio.h>

int main(int argc, char *argv[])
{
  int x;

  printf("x? ");
  scanf("%d", &x);

  printf(x % 2 == 0 ? "even\n" : "odd\n");

  return 0;
}
