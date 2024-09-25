#include <stdio.h>
#define LENGTH 5
#define THRESHOLD 170

int main(int argc, char *argv[])
{
  int heights[LENGTH] = {};

  for (int i = 0; i < LENGTH; i++)
  {
    printf("%d人目の身長? ", i + 1);
    scanf("%d", &heights[i]);
  }

  puts("--- しきい値を超えた人 ---");

  for (int i = 0; i < LENGTH; i++)
  {
    int h = heights[i];

    if (h > THRESHOLD)
    {
      printf("%d人目の身長 %d\n", i + 1, h);
    }
  }

  return 0;
}
