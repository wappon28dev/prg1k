#include <stdio.h>
#define START 1
#define END 10

int main(int argc, char *argv[])
{
  int sum = 0;

  for (int i = START; i <= END; i++)
  {
    sum += i;
  }

  printf("%d\n", sum);

  return 0;
}
