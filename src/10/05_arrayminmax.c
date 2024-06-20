#include <stdio.h>
#define LENGTH 5

int calcMin(int array[])
{
  int min = array[0];
  for (int i = 1; i < LENGTH; i++)
  {
    if (array[i] < min)
    {
      min = array[i];
    }
  }

  return min;
}

int calcMax(int array[])
{
  int max = array[0];
  for (int i = 1; i < LENGTH; i++)
  {
    if (array[i] > max)
    {
      max = array[i];
    }
  }

  return max;
}

int main(int argc, char *argv[])
{
  int heights[LENGTH] = {};

  for (int i = 0; i < LENGTH; i++)
  {
    printf("%d人目の身長? ", i + 1);
    scanf("%d", &heights[i]);
  }

  printf("最小身長は %d\n", calcMin(heights));
  printf("最大身長は %d\n", calcMax(heights));

  return 0;
}
