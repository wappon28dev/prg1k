// REF: https://www.katsuster.net/index.php?arg_date=20210910
#define _GNU_SOURCE

#include <math.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  double radius;

  printf("radius? ");
  scanf("%lf", &radius);

  printf("円周: %lf\n", 2 * M_PI * radius);
  printf("面積: %lf\n", M_PI * radius * radius);

  return 0;
}
