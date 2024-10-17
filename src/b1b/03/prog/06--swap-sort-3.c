#include <stdbool.h>
#include <stdio.h>

void swap(int *p_num1, int *p_num2)
{
  int temp = *p_num1;
  *p_num1 = *p_num2;
  *p_num2 = temp;
}

void sort(int *p_num1, int *p_num2)
{
  bool has_sorted = *p_num1 < *p_num2;
  if (!has_sorted)
  {
    swap(p_num1, p_num2);
  }
}

int main(int argc, char *argv[])
{
  int num1 = 10;
  int num2 = 5;
  int num3 = 15;

  printf("%d, %d, %d\n", num1, num2, num3);

  /*
      +----<2>----+
      |           |
      +-<1>-+     |
      |     |     |
    num1 | num2 | num3
            |     |
            +-<3>-+
  */
  sort(&num1, &num2); // <1>
  sort(&num1, &num3); // <2>
  sort(&num2, &num3); // <3>

  printf("%d, %d, %d\n", num1, num2, num3);

  return 0;
}
