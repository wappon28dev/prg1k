#include <stdio.h>

int draw_figure(int n)
{
  for (int i = 1; i <= n; i++)
  {
    for (int j = 0; j < i; j++)
    {
      printf("*");
    }
    putchar('\n');
  }

  return 0;
}
