#include <stdio.h>
#define START 11
#define END 20

int main(int argc, char *argv[])
{
  int numbers[] = {};

  int delta = END - START;
  for (int i = 0; i <= delta; i++)
  {
    numbers[i] = START + i;
  }

  int sum = 0;

  for (int i = 0; i < END - START + 1; i++)
  {
    sum += numbers[i];
  }

  printf("合計 = %d\n", sum);

  return 0;
}
