#include <stdio.h>

int main(int argc, char *argv[])
{
  int n;

  printf("n? ");
  scanf("%d", &n);

  for (int i = n; i < n + 3; i++)
  {
    for (int j = 1; j <= 9; j++)
    {
      printf("%d x %d = %d\n", i, j, i * j);
    }
  }

  return 0;
}
