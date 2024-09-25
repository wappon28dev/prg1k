#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
  double x;
  int selected;

  printf("x? ");
  scanf("%lf", &x);

  printf(
      "--- menu ---\n"
      "1: 絶対値, 2: 二乗, 3: 三乗\n"
      "menu no? " //
  );

  scanf("%d", &selected);

  switch (selected)
  {
  case 1:
    printf("|%lf| = %lf\n", x, fabs(x));
    break;

  case 2:
    printf("%lf ^ 2 = %f\n", x, pow(x, 2));
    break;

  case 3:
    printf("%lf ^ 3 = %f\n", x, pow(x, 3));
    break;
  }
  return 0;
}
