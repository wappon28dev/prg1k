#include <stdio.h>
#include <stdlib.h>

#define CRANE 2
#define TORTOISE 4

void badInput()
{
  printf("cannot be combined\n");
  exit(1);
}

int main(int argc, char *argv[])
{
  int total, legs;

  printf("total? ");
  scanf("%d", &total);
  printf("legs? ");
  scanf("%d", &legs);

  if (total < 0 || legs < 0)
  {
    badInput();
  }

  // x := crane, y := tortoise, t := total, l := legs, c := CRANE, d := TORTOISE
  // (1) x + y = t
  // ->      x = t - y
  // (2)        c * x + d * y = l
  // ->   c * (t - y) + d * y = l
  // -> c * t - c * y + d * y = l
  // ->   c * t + (d - c) * y = l
  // ->           (d - c) * y = l - c * t
  // ->                     y = (l - c * t) / (d - c)
  // ->                     x = t - y

  int tortoise = (legs - CRANE * total) / (TORTOISE - CRANE);
  int crane = total - tortoise;

  if (crane + tortoise != total || CRANE * crane + TORTOISE * tortoise != legs)
  {
    badInput();
  }

  printf("crane = %d, tortoise = %d\n", crane, tortoise);
  return 0;
}
