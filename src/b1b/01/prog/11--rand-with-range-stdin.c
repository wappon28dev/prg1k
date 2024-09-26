#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand_with_range(int min, int max)
{
  // NOTE:
  // - モジュロバイアスによる乱数の精度に注意.
  // - `random()` は安全だが POSIX 標準でないので注意.
  return rand() % (max - min + 1) + min;
}

int main(int argc, char *argv[])
{
  int min;
  int max;

  printf("min max? ");
  scanf("%d %d", &min, &max);

  if (min > max)
  {
    printf("ERROR: min は max 以下である必要があります. (EXPECTED: %d <= %d).\n", min, max);
    return 1;
  }

  srand((unsigned int)time(NULL));
  printf("%d\n", rand_with_range(min, max));

  return 0;
}
