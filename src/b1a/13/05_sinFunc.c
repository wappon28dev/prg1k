#include <math.h>
#include <stdio.h>

double deg2rad(double deg)
{
  return deg * M_PI / 180;
}

int main(int argc, char *argv[])
{
  double theta;

  printf("input: ");
  scanf("%lf", &theta);

  double rad = deg2rad(theta);
  printf("sin(%lf) = %lf\n", theta, sin(rad));

  return 0;
}
