#include <stdio.h>

int main(int argc, char *argv[])
{
  int a, b;

  printf("a b? ");
  scanf("%d %d", &a, &b);

  if (a > b)
  {
    printf("a > b");
  }
  else if (a == b)
  {
    printf("a == b");
  }
  else
  {
    printf("a < b");
  }

  printf("\n");

  return 0;
}
