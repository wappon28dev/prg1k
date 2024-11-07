#define _GNU_SOURCE

#include <math.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  int r = 10;

  printf("r = %d\n", r);
  printf("S(r) = %f\n", M_PI * r * r);
  printf("l(r) = %f\n", 2 * M_PI * r);

  return 0;
}
