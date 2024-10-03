#include <stdio.h>

extern int draw_figure(int n);

int main(int argc, char *argv[])
{
  int size;

  printf("Size of figure? ");
  scanf("%d", &size);

  draw_figure(size);

  return 0;
}
