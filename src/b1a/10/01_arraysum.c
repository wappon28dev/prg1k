#include <stdio.h>
#define LENGTH 5

int main(int argc, char *argv[])
{
  int evenNumbers[LENGTH] = {0};
  int sum = 0;

  for (int i = 0; i < LENGTH; i++)
  {
    evenNumbers[i] += 2 + i * 2;
  }

  for (int i = 0; i < LENGTH; i++)
  {
    sum += evenNumbers[i];
  }

  printf("合計 = %d\n", sum);

  return 0;
}
