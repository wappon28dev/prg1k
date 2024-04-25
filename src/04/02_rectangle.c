#include <stdio.h>

int main(int argc, char *argv[])
{
  double width, height;

  printf("width? ");
  scanf("%lf", &width);
  printf("height? ");
  scanf("%lf", &height);

  printf("area = %lf\n", width * height);

  return 0;
}
