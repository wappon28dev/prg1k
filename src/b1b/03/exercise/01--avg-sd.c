#include <math.h>
#include <stdio.h>

void set_avg_sd(double *p_avg, double *p_sd, int a, int b)
{
  *p_avg = (a + b) / 2.0;

  // s = √(1/n * Σ(x - x̄)²)
  *p_sd = sqrt((pow(a - *p_avg, 2) + pow(b - *p_avg, 2)) / 2);
}

int main(int argc, char *argv[])
{
  int a;
  int b;

  printf("a b? ");
  scanf("%d %d", &a, &b);

  double avg = 0;
  double sd = 0;

  set_avg_sd(&avg, &sd, a, b);

  printf("avg: %.2f, sd: %.2f\n", avg, sd);

  return 0;
}
