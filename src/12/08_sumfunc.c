#include <stdio.h>

int sumOf(int n)
{
  int sum = 0;

  for (int i = 1; i <= n; i++)
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

  printf("1から%dまでの和は %d\n", n, sumOf(n));

  return 0;
}
