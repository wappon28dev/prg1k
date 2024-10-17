#include <stdio.h>

void set_sum_diff(int *p_sum, int *p_diff, int num1, int num2)
{
  *p_sum = num1 + num2;
  *p_diff = num1 - num2;
}

int main(int argc, char *argv[])
{
  int num1 = 10;
  int num2 = 5;

  int sum = 0;
  int diff = 0;

  set_sum_diff(&sum, &diff, num1, num2);

  printf("%d, %d\n", sum, diff);

  return 0;
}
