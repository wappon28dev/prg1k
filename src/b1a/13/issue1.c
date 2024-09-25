#include <stdio.h>
#include <math.h>

double calcArea(double r)
{
  return M_PI * r * r;
}

double calcCircumference(double r)
{
  return 2 * M_PI * r;
}

int main(int argc, char *argv[])
{
  double r;

  printf("input r: ");
  scanf("%lf", &r);

  printf("%lf %lf\n", calcArea(r), calcCircumference(r));

  return 0;
}
