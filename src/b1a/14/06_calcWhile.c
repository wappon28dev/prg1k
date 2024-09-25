#include <stdio.h>

int calcSum(int start, int end)
{
  int sum = 0;

  while (start <= end)
  {
    sum += start;
    start++;
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
