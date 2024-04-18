#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
  int x;
  int p = 2;

  printf("x? ");
  scanf("%d", &x);

  printf("%d の %d 乗は %d です", x, p, (int)pow(x, p));

  return 0;
}
