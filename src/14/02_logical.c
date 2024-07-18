#include <stdbool.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  int x;

  printf("x? ");
  scanf("%d", &x);

  bool mul2 = x % 2 == 0;
  bool mul3 = x % 3 == 0;

  if (mul2 && mul3)
  {
    puts("2および3の倍数です");
    return 0;
  }

  if (mul2)
  {
    puts("2の倍数です");
  }

  if (mul3)
  {
    puts("3の倍数です");
  }

  if (!mul2 && !mul3)
  {
    puts("2および3の倍数ではありません");
  }

  return 0;
}
