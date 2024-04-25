#include <stdio.h>

int main(int argc, char *argv[])
{
  int nx, ny;

  printf("nx ny? ");
  scanf("%d %d", &nx, &ny);

  printf("nx/ny = %d\n", nx / ny);
  printf("dx/ny = %lf\n", (double)nx / ny);
  printf("nx/dy = %lf\n", nx / (double)ny);

  return 0;
}
