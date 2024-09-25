#include <stdio.h>

int main(int argc, char *argv[])
{
  int a, b;

  printf("a? ");
  scanf("%d", &a);
  printf("b? ");
  scanf("%d", &b);

  printf(a == b ? "aとbの値は等しいです\n" : "");

  printf("計算終了\n");

  return 0;
}
