#include <stdio.h>

int main(int argc, char *argv[])
{
  int n, i, j;

  printf("n? ");
  scanf("%d", &n);

  for (i = n; i < n + 3; i++)
  {
    for (j = 1; j <= 9; j++)
    {
      printf("%d x %d = %d\n", i, j, i * j);
    }
  }

  return 0;
}
