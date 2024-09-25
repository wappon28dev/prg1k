#include <stdio.h>
#include <stdbool.h>

bool isPrime(unsigned int n)
{
  if (n < 2)
  {
    return false;
  }

  for (int i = 2; i < n; i++)
  {
    if (n % i == 0)
    {
      return false;
    }
  }

  return true;
}

int main(int argc, char *argv[])
{
  int n;

  printf("n? ");
  scanf("%u", &n);

  if (n < 0)
  {
    printf("正の整数を入力してください\n");
    return 1;
  }

  printf("素数");
  printf(isPrime(n) ? "です" : "ではありません");
  printf("\n");

  return 0;
}
