#include <stdio.h>

int main(int argc, char *argv[])
{
  int a, b;

  printf("a? ");
  scanf("%d", &a);
  printf("b? ");
  scanf("%d", &b);

  printf(a > 0 && b > 0 ? "aとbは正です" : "aとbのどちらかは負もしくは0です");
  printf("\n");

  return 0;
}
