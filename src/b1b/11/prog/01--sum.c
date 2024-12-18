#include <math.h>
#include <stdio.h>

int sum(int a, int n)
{
  int sum = 0;

  for (int k = 0; k <= n; k++)
  {
    sum += pow(a, n - k);
  }

  return sum;
}

int main(int argc, const char *argv[])
{
  int val = sum(10, 4);

  printf("\\sum_{k=0}^{4} 10^{4-k} = %d\n", val);

  return 0;
}
