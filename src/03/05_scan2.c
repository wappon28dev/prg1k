#include <stdio.h>

int main(int argc, char *argv[])
{
  double a, b;

  printf("a b? ");
  scanf("%lf %lf", &a, &b);
  printf("\na = %f, b = %f\n", a, b);

  return 0;
}
