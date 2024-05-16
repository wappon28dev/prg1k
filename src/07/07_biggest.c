#include <stdio.h>

int main(int argc, char *argv[])
{

  int max = 0;
  for (int i = 0; i < 5; i++)
  {
    int n;
    printf("n? ");
    scanf("%d", &n);

    if (n > max)
    {
      max = n;
    }
  }

  printf("max = %d\n", max);

  return 0;
}
