#include <stdio.h>

int main(int argc, char *argv[])
{
  double dx;

  printf("dx? ");
  scanf("%lf", &dx);

  printf("dx/2 = %lf\n", dx / 2);
  printf("nx = %d\n", (int)dx);
  printf("nx/2 = %d\n", (int)dx / 2);

  return 0;
}
