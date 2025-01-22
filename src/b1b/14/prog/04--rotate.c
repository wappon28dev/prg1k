#include <math.h>
#include <stdio.h>

// 命名ぇ...  snake_case にしたいぃ...
unsigned rrotate(unsigned int x, int n)
{
  unsigned int w = sizeof(unsigned int) << 3;
  unsigned int mask = 0xff;
  return mask & ((x >> n) | (x << (w - n)));
}

unsigned lrotate(unsigned int x, int n)
{
  unsigned int w = sizeof(unsigned int) << 3;
  unsigned int mask = 0xff;
  return mask & (x << n) | (x >> (w - n));
}

void printbin(unsigned int x)
{
  if (x < 1)
    return;
  printbin(x >> 1);
  printf("%d", x & 1);
}

int main(int argc, const char *argv[])
{
  unsigned int x;

  scanf("%u", &x);
  printbin(x);
  printf("\n");
  printbin(rrotate(x, 1));
  printf("\n");
  printbin(lrotate(x, 1));

  return 0;
}
