#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
  double theta;

  printf("input: ");
  scanf("%lf", &theta);

  double rad = theta * M_PI / 180;
  printf("sin(%lf) = %lf\n", theta, sin(rad));

  return 0;
}
