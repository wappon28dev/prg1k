#include <stdio.h>

int main(int argc, char *argv[])
{
  int x;

  printf("x? ");
  scanf("%d", &x);

  printf("%d\n", x * x);

  return 0;
}
