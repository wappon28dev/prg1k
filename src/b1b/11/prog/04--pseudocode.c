#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int rand_with_range(int min, int max)
{
  // NOTE:
  // - モジュロバイアスによる乱数の精度に注意.
  // - `random()` は安全だが POSIX 標準でないので注意.
  return rand() % (max - min + 1) + min;
}

void shuffle(int a[], int n)
{
  srand(time(NULL));
  for (int i = n - 1; i >= 1; i--)
  {
    int j = rand_with_range(0, i);
    swap(&a[j], &a[i]);
  }
}

int main(int argc, const char *argv[])
{
  int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  shuffle(a, 10);

  for (int i = 0; i < 10; i++)
  {
    printf("%d ", a[i]);
  }

  printf("\n");

  return 0;
}
