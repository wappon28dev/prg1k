#include <stdio.h>

int draw_figure(int n)
{
  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= i; j++)
    {
      printf(i == j ? "*" : " ");
    }
    putchar('\n');
  }

  return 0;
}
