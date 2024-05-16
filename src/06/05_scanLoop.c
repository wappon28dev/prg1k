#include <stdio.h>

int main(int argc, char *argv[])
{

  for (int i = 1; i <= 5; i++)
  {
    int a;

    printf("a? ");
    scanf("%d", &a);

    printf("%d: %d\n", i, a);
  }

  return 0;
}
