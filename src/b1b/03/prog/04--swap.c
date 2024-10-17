#include <stdio.h>

void swap(int *p_num1, int *p_num2)
{
  int temp = *p_num1;
  *p_num1 = *p_num2;
  *p_num2 = temp;
}

int main(int argc, char *argv[])
{
  int num1 = 10;
  int num2 = 5;

  printf("%d, %d\n", num1, num2);

  swap(&num1, &num2);

  printf("%d, %d\n", num1, num2);

  return 0;
}
