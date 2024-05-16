#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
  int x, n;

  printf("x n? ");
  scanf("%d %d", &x, &n);

  printf("%d^%d = %d\n", x, n, (int)pow(x, n));

  return 0;
}
