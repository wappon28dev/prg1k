#include <stdio.h>

int main(int argc, char *argv[])
{
  int height, weight;

  printf("height? ");
  scanf("%d", &height);
  printf("weight? ");
  scanf("%d", &weight);

  printf("standardWeight = %lf\n", (height - 100) * 0.9);

  float heightM = (float)height / 100;
  float bmi = (float)weight / (heightM * heightM);
  printf("BMI = %lf\n", bmi);

  return 0;
}
