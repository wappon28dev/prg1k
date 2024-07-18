#include <stdio.h>

int calcSum(int start, int end)
{
  int sum = 0;

  for (int i = start; i <= end; i++)
  {
    sum += i;
  }

  return sum;
}

int main(int argc, char *argv[])
{
  int n;

  printf("n? ");
  scanf("%d", &n);

  printf("1から%dまでの和は %d\n", n, calcSum(1, n));

  return 0;
}
