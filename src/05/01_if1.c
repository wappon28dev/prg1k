#include <stdio.h>

int main(int argc, char *argv[])
{
  int a;

  printf("a? ");
  scanf("%d", &a);

  if (a > 0)
  {
    printf("aは正の値です\n");
  }

  printf("計算終了\n");

  return 0;
}
