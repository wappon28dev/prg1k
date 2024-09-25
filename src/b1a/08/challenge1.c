#include <stdio.h>

int main(int argc, char *argv[])
{
  int n;

  printf("input? ");
  scanf("%d", &n);

  for (int i = 2; i <= n; i++)
  {
    while (n % i == 0)
    {
      printf("%d", i);
      if (n != i)
      {
        printf(", ");
      }

      n /= i;
    }
  }

  printf("\n");

  return 0;
}
