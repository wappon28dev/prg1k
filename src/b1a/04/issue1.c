#include <stdio.h>

int main(int argc, char *argv[])
{
  int height, weight;

  printf("height? ");
  scanf("%d", &height);
  printf("weight? ");
  scanf("%d", &weight);

  printf("standardWeight = %lf\n", (height - 100) * 0.9);

  double heightM = (double)height / 100;
  double bmi = (double)weight / (heightM * heightM);
  printf("BMI = %lf\n", bmi);

  return 0;
}
