#include <stdio.h>

int main(int argc, char *argv[])
{
  int n, x;

  printf("n x? ");
  scanf("%d %d", &n, &x);

  int count = 0;
  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= n; j++)
    {
      for (int k = 1; k <= n; k++)
      {
        if (i + j + k == x)
        {
          printf("%d%d%d\n", i, j, k);
          count++;
        }
      }
    }
  }

  printf("組み合わせの数: %d\n", count);

  return 0;
}
