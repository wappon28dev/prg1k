#include <stdio.h>

void good_swap(int *p_a, int *p_b)
{
  int temp = *p_a;
  *p_a = *p_b;
  *p_b = temp;
}

void bad_swap(int *p_a, int *p_b)
{
  int *p_temp = p_a;
  // NOTE: ここで `p_a` を `p_b` に差し替えても, スコープ外なので意味がない
  p_a = p_b;
  p_b = p_temp;
}

int main(int argc, char *argv[])
{
  int num1 = 10;
  int num2 = 5;

  printf("%d, %d\n", num1, num2);

  good_swap(&num1, &num2);
  printf("%d, %d\n", num1, num2);

  num1 = 10;
  num2 = 5;

  bad_swap(&num1, &num2);
  printf("%d, %d\n", num1, num2);

  return 0;
}
