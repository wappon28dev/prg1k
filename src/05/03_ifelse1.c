#include <stdio.h>

int main(int argc, char *argv[])
{
  int a;

  printf("a? ");
  scanf("%d", &a);

  printf(a >= 0 ? "aは正の値もしくは0です" : "aは負の値です");
  printf("\n");

  printf("計算終了\n");

  return 0;
}
