#include <math.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  int x1 = 100;
  int y1 = 10;
  int x2 = 200;
  int y2 = 20;

  printf("ユークリッド距離: %f\n", sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));

  return 0;
}
