#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum
{
  UNDERWEIGHT,
  NORMAL,
  OBESITY,
  EXTREME_OBESITY
} BMIStatus;

BMIStatus calc_bmi_status(double height, double weight)
{
  double bmi = weight / (height * height);

  if (bmi < 18.5)
  {
    return UNDERWEIGHT;
  }
  else if (bmi < 25)
  {
    return NORMAL;
  }
  else if (bmi < 30)
  {
    return OBESITY;
  }
  else
  {
    return EXTREME_OBESITY;
  }
}

const char *bmi_status_to_str(BMIStatus status)
{
  switch (status)
  {
  case UNDERWEIGHT:
    return "やせ";
  case NORMAL:
    return "標準";
  case OBESITY:
    return "肥満";
  case EXTREME_OBESITY:
    return "高度肥満";
  }
}

int main(int argc, char *argv[])
{
  int height;
  int weight;

  printf("height (cm)? ");
  scanf("%d", &height);

  printf("weight (kg)? ");
  scanf("%d", &weight);

  BMIStatus status = calc_bmi_status(height / 100.0, weight);

  puts(bmi_status_to_str(status));

  return 0;
}
