#include <stdio.h>

int main(int argc, char *argv[])
{
  int w, h;

  printf("h w? ");
  scanf("%d %d", &h, &w);

  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      printf("#");
    }
    printf("\n");
  }

  return 0;
}
