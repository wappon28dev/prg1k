#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
  int sum = 0;

  while (true)
  {
    int x;
    printf("x? ");
    scanf("%d", &x);

    sum += x;
    printf("sum: %d\n", sum);

    if (x == 0)
    {
      break;
    }
  }

  printf("end\n");

  return 0;
}
