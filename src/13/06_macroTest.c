#include <stdio.h>
#define NUM 10

int main(int argc, char *argv[])
{
  int sum = 0;

  for (int i = 1; i <= NUM; i++)
  {
    sum += i;
  }

  printf("総和 = %d\n", sum);

  return 0;
}
