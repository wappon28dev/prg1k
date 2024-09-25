#include <stdio.h>

int main(int argc, char *argv[])
{
  int a, b;

  printf("a? ");
  scanf("%d", &a);
  printf("b? ");
  scanf("%d", &b);

  if (a > 0)
  {
    if (b == 0)
    {
      printf("A");
    }
    else if (b > 0)
    {
      printf("B");
    }
    else
    {
      printf("C");
    }
  }
  else
  {
    printf("D");
  }

  printf("\n");

  return 0;
}
