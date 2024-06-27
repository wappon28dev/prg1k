#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#define MAX 100

bool isPrime(unsigned int n, int primeNums[], int primeNumsLastIdx)
{
  if (n < 2)
  {
    return false;
  }

  for (int i = 0; i < primeNumsLastIdx; i++)
  {
    if (n % primeNums[i] == 0)
    {
      return false;
    }
  }

  return true;
}

int main(int argc, char *argv[])
{
  int primeNums[MAX + 1] = {0};
  int primeNumsLastIdx = 0;

  for (int i = 0; i < MAX; i++)
  {
    if (isPrime(i, primeNums, primeNumsLastIdx))
    {
      primeNums[primeNumsLastIdx] = i;
      primeNumsLastIdx++;
    }
  }

  for (int i = 0; i < primeNumsLastIdx; i++)
  {
    printf("%d, ", primeNums[i]);
  }

  puts("");

  return 0;
}
