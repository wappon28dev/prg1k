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

    if (x == 0)
    {
      break;
    }

    sum += x;
  }

  printf("sum: %d\n", sum);
  printf("end\n");

  return 0;
}
