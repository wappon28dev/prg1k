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
  srand((unsigned int)time(NULL));
  printf("%d\n", rand_with_range(3, 5));

  return 0;
}
