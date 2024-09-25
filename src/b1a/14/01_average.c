#include <stdio.h>

int main(int argc, char *argv[])
{
  int h1, h2, h3;

  printf("1人目の身長は? ");
  scanf("%d", &h1);

  printf("2人目の身長は? ");
  scanf("%d", &h2);

  printf("3人目の身長は? ");
  scanf("%d", &h3);

  printf("平均身長は %lf\n", (double)(h1 + h2 + h3) / 3);

  return 0;
}
