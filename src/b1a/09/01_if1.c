#include <stdio.h>

int main(int argc, char *argv[])
{
  int n;

  printf("n? ");
  scanf("%d", &n);

  if (n == 1)
  {
    printf("AAA");
  }
  else if (n == 2)
  {
    printf("BBB");
  }
  else
  {
    printf("Defaultです.");
  }

  printf("\n");

  return 0;
}
