#include <stdio.h>

int main(int argc, char *argv[])
{
  int x;

  printf("x? ");
  scanf("%d", &x);

  // WORK-AROUND: 問題の修正があれば直す
  if (x == 0)
  {
    printf("2の倍数ではありません\n3の倍数ではありません\n");
    return 0;
  }

  printf(x % 2 == 0 ? "2の倍数です" : "2の倍数ではありません");
  printf("\n");

  printf(x % 3 == 0 ? "3の倍数です" : "3の倍数ではありません");
  printf("\n");

  return 0;
}
