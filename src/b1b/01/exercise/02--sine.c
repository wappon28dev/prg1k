// REF: https://www.katsuster.net/index.php?arg_date=20210910
#define _GNU_SOURCE

#include <math.h>
#include <stdio.h>

double deg2rad(int deg)
{
  return deg * M_PI / 180;
}

int main(int argc, char *argv[])
{
  for (int deg = 0; deg <= 360; deg += 10)
  {
    printf("sin%d° = %lf\n", deg, sin(deg2rad(deg)));
  }

  return 0;
}
