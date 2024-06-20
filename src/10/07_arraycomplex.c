#include <stdio.h>
#define LENGTH 5
#define THRESHOLD 23

struct BodyMeasurements
{
  int height;
  int weight;
};

typedef struct BodyMeasurements BodyMeasurements;

int main(int argc, char *argv[])
{
  BodyMeasurements bmList[LENGTH] = {};

  for (int i = 0; i < LENGTH; i++)
  {
    printf("%d人目の身長と体重? ", i + 1);
    scanf("%d %d", &bmList[i].height, &bmList[i].weight);
  }

  puts("--- しきい値を超えた人 ---");

  for (int i = 0; i < LENGTH; i++)
  {
    BodyMeasurements bm = bmList[i];
    double standardWeight = (bm.height - 100) * 0.9;
    double heightM = bm.height / 100.0;
    double bmi = bm.weight / (heightM * heightM);

    double diff = bm.weight - standardWeight;

    if (bmi > THRESHOLD)
    {
      printf("%d人目のBMI: %lf, 標準体重との差: %lf\n", i + 1, bmi, diff);
    }
  }

  return 0;
}
