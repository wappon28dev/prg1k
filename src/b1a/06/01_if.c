#include <stdio.h>

int main(int argc, char *argv[])
{
  int a;

  printf("a? ");
  scanf("%d", &a);

  printf("aは");
  if (a < 0)
  {
    printf("負の値");
  }
  else if (a == 0)
  {
    printf("0");
  }
  else
  {
    printf("正の値");
  }
  printf("です\n");

  return 0;
}
