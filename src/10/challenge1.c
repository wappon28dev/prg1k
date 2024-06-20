#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#define MAX 100

void sieveOfEratosthenes(int max, bool isPrime[])
{
  for (int i = 2; i <= max; i++)
  {
    isPrime[i] = true;
  }

  for (int p = 2; p * p <= max; p++)
  {
    if (isPrime[p])
    {
      for (int i = p * p; i <= max; i += p)
      {
        isPrime[i] = false;
      }
    }
  }
}

int main(int argc, char *argv[])
{
  bool isPrime[MAX + 1] = {false};

  sieveOfEratosthenes(MAX, isPrime);

  for (int i = 2; i <= MAX; i++)
  {
    if (isPrime[i])
    {
      printf("%d", i);
      if (i < MAX)
      {
        printf(",");

        if (i != MAX - 1)
        {
          printf(" ");
        }
      }
    }
  }

  puts("");

  return 0;
}
