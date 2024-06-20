#include <stdio.h>
#define LENGTH 5

int main(int argc, char *argv[])
{
  int heights[LENGTH] = {};

  for (int i = 0; i < LENGTH; i++)
  {
    printf("%d人目の身長? ", i + 1);
    scanf("%d", &heights[i]);
  }

  double sum = 0;
  for (int i = 0; i < LENGTH; i++)
  {
    sum += heights[i];
  }

  printf("平均身長 = %lf\n", sum / LENGTH);

  return 0;
}
