#include <stdio.h>
#include <limits.h>

int main(int argc, char *argv[])
{

  int max = INT_MIN;
  for (int i = 1; i <= 5; i++)
  {
    int n;
    printf("%d? ", i);
    scanf("%d", &n);

    if (n > max)
    {
      max = n;
    }
  }

  printf("max = %d\n", max);

  return 0;
}
