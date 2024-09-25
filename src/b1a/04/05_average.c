#include <stdio.h>

int main(int argc, char *argv[])
{
  int h1, h2, h3;

  printf("h1? ");
  scanf("%d", &h1);
  printf("h2? ");
  scanf("%d", &h2);
  printf("h3? ");
  scanf("%d", &h3);

  printf("average = %lf\n", (h1 + h2 + h3) / 3.0);

  return 0;
}
